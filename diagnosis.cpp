#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

extern "C" void initialize();  // Declare initialize as a function to be exported

unordered_map<string, int> clauseVariableList;
unordered_map<int, string> clauseToRule;
unordered_map<int, string> ruleToDiagnosis;
unordered_map<string, vector<string>> diagnosisToTreatments;

void initialize() {
    clauseVariableList = {
        {"Lower belly, groin or back pain", 1},
        {"Pain or discomfort in the testicle", 2},
        {"Swelling or heaviness of scrotum", 3},
        {"Lumps or swelling of the testicles", 4},
        {"Sudden weight loss", 5},
        {"Blood in urine or semen", 6},
        {"Trouble with urination", 7},
        {"Bone pain", 8},
        {"Fatigue", 9},
        {"Coughing or wheezing", 10},
        {"Chest pain", 11},
        {"Shortness of breath", 12},
        {"Coughing up blood", 13},
        {"Feeling of discomfort", 14},
        {"Swollen neck, armpit or groin glands", 15},
        {"Yellowing of eyes or skin", 16},
        {"Dark colored urine", 17},
        {"Belly or back pain", 18},
        {"Difficulty swallowing", 19},
        {"Heavy smoker or drinker", 20},
        {"History of GERD", 21},
        {"Abdominal bloating", 22},
        {"Discomfort in pelvic region", 23},
        {"Constipation or frequent urination", 24},
        {"Uncommon vaginal bleeding", 25},
        {"Watery discharge with blood or strong odor", 26},
        {"Painful bowel movements or urination", 27},
        {"Lump in the breast", 28},
        {"Flattened or inverted nipple", 29},
        {"Changes in shape, color or size of breast", 30},
        {"Peeling, flaking or crusting of breast skin", 31}
    };

    // Correcting the mapping of symptoms to cancers
    ruleToDiagnosis = {
        {1, "Testicular Cancer"}, {2, "Testicular Cancer"}, {3, "Testicular Cancer"}, {4, "Testicular Cancer"},
        {5, "Pancreatic Cancer"}, {6, "Prostate Cancer"}, {7, "Prostate Cancer"}, {8, "Prostate Cancer"},
        {9, "Lymphoma"}, {9, "Lung Cancer"}, {9, "Pancreatic Cancer"}, {9, "Ovarian Cancer"}, {9, "Cervical Cancer"},
        {10, "Lymphoma"}, {10, "Lung Cancer"},
        {11, "Lymphoma"}, {11, "Lung Cancer"}, {11, "Esophageal Cancer"},
        {12, "Lymphoma"}, {12, "Lung Cancer"},
        {13, "Lymphoma"}, {13, "Lung Cancer"},
        {14, "Lymphoma"},
        {15, "Lymphoma"}, {16, "Pancreatic Cancer"}, {17, "Pancreatic Cancer"},
        {18, "Pancreatic Cancer"}, {19, "Esophageal Cancer"}, {20, "Esophageal Cancer"},
        {21, "Esophageal Cancer"}, {22, "Ovarian Cancer"}, {23, "Ovarian Cancer"}, {24, "Ovarian Cancer"},
        {25, "Cervical Cancer"}, {26, "Cervical Cancer"}, {27, "Cervical Cancer"}, 
        {28, "Breast Cancer"}, {29, "Breast Cancer"}, {30, "Breast Cancer"}, {31, "Breast Cancer"}
    };

    diagnosisToTreatments = {
        {"Testicular Cancer", {"Chemotherapy", "Surgery", "Radiation Therapy"}},
        {"Prostate Cancer", {"Hormone Therapy", "Chemotherapy", "Surgery", "Radiation Therapy"}},
        {"Lymphoma", {"Chemotherapy", "Radiation Therapy", "Immunotherapy", "Stem Cell Transplant"}},
        {"Lung Cancer", {"Chemotherapy", "Radiation Therapy", "Surgery", "Immunotherapy"}},
        {"Pancreatic Cancer", {"Chemotherapy", "Surgery", "Radiation Therapy", "Targeted Therapy"}},
        {"Esophageal Cancer", {"Chemotherapy", "Radiation Therapy", "Surgery", "Immunotherapy"}},
        {"Ovarian Cancer", {"Chemotherapy", "Surgery", "Targeted Therapy", "Immunotherapy"}},
        {"Cervical Cancer", {"Chemotherapy", "Radiation Therapy", "Surgery", "Immunotherapy"}},
        {"Breast Cancer", {"Chemotherapy", "Surgery", "Radiation Therapy", "Hormone Therapy"}}
    };
}

void update_VL(int Ci) {
    cout << "Updating Variable List for clause " << Ci << endl;
}

void search_cvl(string variable) {
    if (clauseVariableList.find(variable) != clauseVariableList.end()) {
        cout << "Variable " << variable << " found with clause number " << clauseVariableList[variable] << endl;
    } else {
        cout << "Variable " << variable << " not found." << endl;
    }
}

// Improved diagnoseCancer function
extern "C" const char* diagnoseCancer(const char* symptomsJson) {
    string symptoms(symptomsJson);  // Convert symptomsJson to string
    stringstream ss(symptoms);
    string symptom;

    vector<int> matchedClauses;
    vector<string> matchedSymptoms; // To store matched symptoms

    // Parse the symptomsJson to identify matching symptoms
    while (getline(ss, symptom, ',')) {
        cout << "Processing symptom: " << symptom << endl;  // Debugging line

        if (clauseVariableList.find(symptom) != clauseVariableList.end()) {
            int clause = clauseVariableList[symptom];
            matchedClauses.push_back(clause);
            matchedSymptoms.push_back(symptom); // Store matched symptoms
            cout << "Matched symptom: " << symptom << " with clause: " << clause << endl;
        } else {
            cout << "No match found for symptom: " << symptom << endl;  // Debugging line
        }
    }

    // If no symptoms match, return an unknown diagnosis
    if (matchedClauses.empty()) {
        return "{\"diagnosis\":\"Unknown diagnosis\", \"treatments\":[]}";
    }

    // Logic for diagnosing based on matched clauses
    string diagnosis = "Unknown diagnosis";
    vector<string> treatments;

    // For each matched clause, find the associated diagnosis
    unordered_map<string, int> cancerCounts;
    for (int clause : matchedClauses) {
        if (ruleToDiagnosis.find(clause) != ruleToDiagnosis.end()) {
            string cancerDiagnosis = ruleToDiagnosis[clause];
            cancerCounts[cancerDiagnosis]++;
        }
    }

    // Find the cancer with the most matches (i.e., highest frequency of matching symptoms)
    int maxCount = 0;
    for (auto& entry : cancerCounts) {
        if (entry.second > maxCount) {
            diagnosis = entry.first;
            maxCount = entry.second;
        }
    }

    // Add treatment options based on diagnosis
    if (diagnosisToTreatments.find(diagnosis) != diagnosisToTreatments.end()) {
        treatments = diagnosisToTreatments[diagnosis];
    }

    // Prepare the JSON response with diagnosis and treatments
    string resultJson = "{\"diagnosis\":\"" + diagnosis + "\", \"treatments\":[";
    for (size_t i = 0; i < treatments.size(); ++i) {
        resultJson += "\"" + treatments[i] + "\"";
        if (i != treatments.size() - 1) resultJson += ", ";
    }
    resultJson += "]}";

    // Allocate memory for the result and return the C-string
    char* resultCStr = (char*)malloc(resultJson.size() + 1);
    strcpy(resultCStr, resultJson.c_str());

    return resultCStr;  // Return pointer to the allocated memory
}

extern "C" void freeDiagnosisResult(char* diagnosisResult) {
    free(diagnosisResult);
}
