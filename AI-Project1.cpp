#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// Clause Variable List (Symptom -> Clause Number)
unordered_map<string, int> clauseVariableList;

void initializeClauseVariableList() {
    clauseVariableList["Lower belly, groin or back pain"] = 1;
    clauseVariableList["Pain or discomfort in the testicle"] = 2;
    clauseVariableList["Swelling or heaviness of scrotum"] = 3;
    clauseVariableList["Lumps or swelling of the testicles"] = 4;
    clauseVariableList["Sudden weight loss"] = 5;
    clauseVariableList["Blood in urine or semen"] = 6;
    clauseVariableList["Trouble with urination"] = 7;
    clauseVariableList["Bone pain"] = 8;
    clauseVariableList["Fatigue"] = 9;
    clauseVariableList["Coughing or wheezing"] = 10;
    clauseVariableList["Chest pain"] = 11;
    clauseVariableList["Shortness of breath"] = 12;
    clauseVariableList["Coughing up blood"] = 13;
    clauseVariableList["Feeling of discomfort"] = 14;
    clauseVariableList["Swollen neck, armpit or groin glands"] = 15;
    clauseVariableList["Yellowing of eyes or skin"] = 16;
    clauseVariableList["Dark colored urine"] = 17;
    clauseVariableList["Belly or back pain"] = 18;
    clauseVariableList["Difficulty swallowing"] = 19;
    clauseVariableList["Heavy smoker or drinker"] = 20;
    clauseVariableList["History of GERD"] = 21;
    clauseVariableList["Abdominal bloating"] = 22;
    clauseVariableList["Discomfort in pelvic region"] = 23;
    clauseVariableList["Constipation or frequent urination"] = 24;
    clauseVariableList["Uncommon vaginal bleeding"] = 25;
    clauseVariableList["Watery discharge with blood or strong odor"] = 26;
    clauseVariableList["Painful bowel movements or urination"] = 27;
    clauseVariableList["Lump in the breast"] = 28;
    clauseVariableList["Flattened or inverted nipple"] = 29;
    clauseVariableList["Changes in shape, color or size of breast"] = 30;
    clauseVariableList["Peeling, flaking or crusting of breast skin"] = 31;
}

// Rule Mapping
unordered_map<int, string> ruleList;

void initializeRuleList() {
    ruleList[1] = "Testicular Cancer";
    ruleList[2] = "Prostate Cancer";
    ruleList[3] = "Lymphoma";
    ruleList[4] = "Lung Cancer";
    ruleList[5] = "Pancreatic Cancer";
    ruleList[6] = "Esophageal Cancer";
    ruleList[7] = "Ovarian Cancer";
    ruleList[8] = "Cervical Cancer";
    ruleList[9] = "Breast Cancer";
}

// Treatment Mapping (based on diagnosis)
unordered_map<string, vector<string>> treatmentOptions;

void initializeTreatmentOptions() {
    treatmentOptions["Testicular Cancer"] = {"Surgery", "Chemotherapy", "Radiation Therapy"};
    treatmentOptions["Prostate Cancer"] = {"Surgery", "Radiation Therapy", "Hormone Therapy"};
    treatmentOptions["Lymphoma"] = {"Chemotherapy", "Radiation Therapy", "Stem Cell Transplant"};
    treatmentOptions["Lung Cancer"] = {"Surgery", "Chemotherapy", "Radiation Therapy", "Immunotherapy"};
    treatmentOptions["Pancreatic Cancer"] = {"Surgery", "Chemotherapy", "Palliative Care"};
    treatmentOptions["Esophageal Cancer"] = {"Surgery", "Chemotherapy", "Radiation Therapy"};
    treatmentOptions["Ovarian Cancer"] = {"Surgery", "Chemotherapy", "Targeted Therapy"};
    treatmentOptions["Cervical Cancer"] = {"Surgery", "Chemotherapy", "Radiation Therapy"};
    treatmentOptions["Breast Cancer"] = {"Surgery", "Chemotherapy", "Radiation Therapy", "Hormone Therapy"};
}

// Global Derived Conclusion List
vector<string> derivedConclusions;
queue<string> globalConclusionQueue;

// Function Prototypes
void process(string variable);
void search_cvl(string variable);
void clause_to_rule(int Ci);
void update_VL(int Ci);
void validate_Ri(int Ri);
void FC_main();

// Function Implementations
void search_cvl(string variable) {
    if (clauseVariableList.find(variable) != clauseVariableList.end()) {
        int Ci = clauseVariableList[variable];
        update_VL(Ci);
        clause_to_rule(Ci);
    }
}

void clause_to_rule(int Ci) {
    int Ri = ((Ci - 1) / 4 + 1) * 10; // Assuming rules are numbered as 10, 20, 30...
    validate_Ri(Ri);
}

void update_VL(int Ci) {
    globalConclusionQueue.push(to_string(Ci));
}

void validate_Ri(int Ri) {
    if (ruleList.find(Ri / 10) != ruleList.end()) {
        string diagnosis = ruleList[Ri / 10];
        derivedConclusions.push_back(diagnosis);
        globalConclusionQueue.push(diagnosis);
    }
}

void process(string variable) {
    search_cvl(variable);
}

void FC_main() {
    string response;
    cout << "Do you suspect having cancer? (yes/no): ";
    cin >> response;
    if (response != "yes") {
        cout << "No diagnosis needed." << endl;
        return;
    }
    
    cout << "Enter your gender (Male/Female): ";
    string gender;
    cin >> gender;
    cin.ignore(); // Clear the newline character
    
    cout << "Here is a list of symptoms. Type each symptom you have, one per line. Type 'done' when finished:\n";
    for (const auto& symptom : clauseVariableList) {
        cout << "- " << symptom.first << endl;
    }
    
    string symptomInput;
    while (true) {
        getline(cin, symptomInput);
        if (symptomInput == "done") break;
        process(symptomInput);
    }

    cout << "\nDerived Diagnoses:\n";
    for (const auto& diagnosis : derivedConclusions) {
        cout << "- " << diagnosis << endl;
        // Display treatment options
        cout << "Treatment Options for " << diagnosis << ":\n";
        if (treatmentOptions.find(diagnosis) != treatmentOptions.end()) {
            for (const auto& treatment : treatmentOptions[diagnosis]) {
                cout << "  - " << treatment << endl;
            }
        }
    }
}

int main() {
    initializeClauseVariableList();
    initializeRuleList();
    initializeTreatmentOptions();  // Initialize treatment options
    FC_main();
    return 0;
}
