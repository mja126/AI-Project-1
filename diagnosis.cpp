#include <emscripten.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;

// Clause Variable List (Symptom -> Clause Number)
unordered_map<string, int> clauseVariableList;
unordered_map<int, string> ruleList;
unordered_map<string, vector<string>> treatmentOptions;
vector<string> derivedConclusions;
queue<string> globalConclusionQueue;

// Function to initialize symptoms
void initializeClauseVariableList() {
    clauseVariableList = {
        {"Lower belly, groin or back pain", 1}, {"Pain or discomfort in the testicle", 2}, {"Swelling or heaviness of scrotum", 3},
        {"Lumps or swelling of the testicles", 4}, {"Sudden weight loss", 5}, {"Blood in urine or semen", 6}, {"Trouble with urination", 7},
        {"Bone pain", 8}, {"Fatigue", 9}, {"Coughing or wheezing", 10}, {"Chest pain", 11}, {"Shortness of breath", 12},
        {"Coughing up blood", 13}, {"Feeling of discomfort", 14}, {"Swollen neck, armpit or groin glands", 15},
        {"Yellowing of eyes or skin", 16}, {"Dark colored urine", 17}, {"Belly or back pain", 18}, {"Difficulty swallowing", 19},
        {"Heavy smoker or drinker", 20}, {"History of GERD", 21}, {"Abdominal bloating", 22}, {"Discomfort in pelvic region", 23},
        {"Constipation or frequent urination", 24}, {"Uncommon vaginal bleeding", 25}, {"Watery discharge with blood or strong odor", 26},
        {"Painful bowel movements or urination", 27}, {"Lump in the breast", 28}, {"Flattened or inverted nipple", 29},
        {"Changes in shape, color or size of breast", 30}, {"Peeling, flaking or crusting of breast skin", 31}
    };
}

// Function to initialize diagnosis rules
void initializeRuleList() {
    ruleList = {
        {1, "Testicular Cancer"}, {2, "Prostate Cancer"}, {3, "Lymphoma"}, {4, "Lung Cancer"},
        {5, "Pancreatic Cancer"}, {6, "Esophageal Cancer"}, {7, "Ovarian Cancer"},
        {8, "Cervical Cancer"}, {9, "Breast Cancer"}
    };
}

// Function to initialize treatment options
void initializeTreatmentOptions() {
    treatmentOptions = {
        {"Testicular Cancer", {"Surgery", "Chemotherapy", "Radiation Therapy"}},
        {"Prostate Cancer", {"Surgery", "Radiation Therapy", "Hormone Therapy"}},
        {"Lymphoma", {"Chemotherapy", "Radiation Therapy", "Stem Cell Transplant"}},
        {"Lung Cancer", {"Surgery", "Chemotherapy", "Radiation Therapy", "Immunotherapy"}},
        {"Pancreatic Cancer", {"Surgery", "Chemotherapy", "Palliative Care"}},
        {"Esophageal Cancer", {"Surgery", "Chemotherapy", "Radiation Therapy"}},
        {"Ovarian Cancer", {"Surgery", "Chemotherapy", "Targeted Therapy"}},
        {"Cervical Cancer", {"Surgery", "Chemotherapy", "Radiation Therapy"}},
        {"Breast Cancer", {"Surgery", "Chemotherapy", "Radiation Therapy", "Hormone Therapy"}}
    };
}

// Search for a symptom in the clause variable list
void search_cvl(string variable) {
    if (clauseVariableList.find(variable) != clauseVariableList.end()) {
        int Ci = clauseVariableList[variable];
        globalConclusionQueue.push(to_string(Ci));
    }
}

// Convert Clause to Rule
void process(string variable) {
    search_cvl(variable);
    while (!globalConclusionQueue.empty()) {
        string clause = globalConclusionQueue.front();
        globalConclusionQueue.pop();
        int ruleNum = (stoi(clause) - 1) / 4 + 1;
        if (ruleList.find(ruleNum) != ruleList.end()) {
            derivedConclusions.push_back(ruleList[ruleNum]);
        }
    }
}

// Diagnose cancer based on symptoms received from JavaScript
extern "C" EMSCRIPTEN_KEEPALIVE const char* diagnoseCancer(const char* symptomsJson) {
    // Reset previous conclusions
    derivedConclusions.clear();

    // Parse symptoms (comma-separated)
    string symptomsStr(symptomsJson);
    vector<string> selectedSymptoms;
    size_t pos = 0;
    while ((pos = symptomsStr.find(",")) != string::npos) {
        selectedSymptoms.push_back(symptomsStr.substr(0, pos));
        symptomsStr.erase(0, pos + 1);
    }
    selectedSymptoms.push_back(symptomsStr);

    // Process each symptom
    for (const auto& symptom : selectedSymptoms) {
        process(symptom);
    }

    // Determine best diagnosis
    string bestMatch = derivedConclusions.empty() ? "No cancer suspected" : derivedConclusions[0];

    // Create JSON response
    ostringstream response;
    response << "{ \"diagnosis\": \"" << bestMatch << "\", \"treatments\": [";

    if (treatmentOptions.find(bestMatch) != treatmentOptions.end()) {
        const vector<string>& treatmentList = treatmentOptions[bestMatch];
        for (size_t i = 0; i < treatmentList.size(); ++i) {
            response << "\"" << treatmentList[i] << "\"";
            if (i != treatmentList.size() - 1) response << ",";
        }
    }

    response << "] }";

    // Copy response to a static buffer and return pointer to JavaScript
    static string result;
    result = response.str();
    return result.c_str();
}

// Initialize everything
extern "C" EMSCRIPTEN_KEEPALIVE void initialize() {
    initializeClauseVariableList();
    initializeRuleList();
    initializeTreatmentOptions();
}
