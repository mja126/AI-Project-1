#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

// Global Lists and Variables
unordered_map<string, string> variableList;  // Variable to value mapping
unordered_map<int, string> ruleList;     // Rule number to diagnosis mapping
unordered_map<string, int> clauseVariableList;  // Mapping symptoms to clause numbers
unordered_map<int, vector<string>> ruleClauses;  // Rule to clause variables mapping
unordered_map<string, vector<string>> treatmentOptions;  // Diagnosis to treatment mapping
unordered_map<string, string> derivedGlobalVariableList;  // List of derived global conclusions

// Backward Chaining Functions
int search_con(const string& variable);
int rule_to_clause(int ruleNumber);
void update_VL(int Ci);
void validate_Ri(int Ri, string& conclusion);
void process(const string& variable);
void backward_chaining(const string& goalVariable);

// Forward Chaining Function (for treatment)
void forward_chaining(const string& diagnosis);

// Initialize the system with rules, symptoms, and treatments
void initialize() {
    // Initialize symptoms and their corresponding clause numbers
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

    // Initialize ruleList with diagnosis (Rule numbers mapped to diagnosis)
    ruleList[1] = "Testicular Cancer";
    ruleList[2] = "Prostate Cancer";
    ruleList[3] = "Lymphoma";
    ruleList[4] = "Lung Cancer";
    ruleList[5] = "Pancreatic Cancer";
    ruleList[6] = "Esophageal Cancer";
    ruleList[7] = "Ovarian Cancer";
    ruleList[8] = "Cervical Cancer";
    ruleList[9] = "Breast Cancer";

    // Initialize treatment options for each cancer
    treatmentOptions["Testicular Cancer"] = {"Surgery", "Chemotherapy", "Radiation therapy"};
    treatmentOptions["Prostate Cancer"] = {"Surgery", "Hormone therapy", "Radiation therapy"};
    treatmentOptions["Lymphoma"] = {"Chemotherapy", "Stem cell transplant"};
    treatmentOptions["Lung Cancer"] = {"Chemotherapy", "Immunotherapy", "Radiation therapy"};
    treatmentOptions["Pancreatic Cancer"] = {"Surgery", "Chemotherapy", "Targeted therapy"};
    treatmentOptions["Esophageal Cancer"] = {"Surgery", "Chemotherapy", "Radiation therapy"};
    treatmentOptions["Ovarian Cancer"] = {"Surgery", "Chemotherapy", "Targeted therapy"};
    treatmentOptions["Cervical Cancer"] = {"Surgery", "Chemotherapy", "Radiation therapy"};
    treatmentOptions["Breast Cancer"] = {"Surgery", "Chemotherapy", "Hormone therapy", "Immunotherapy"};

    // Initialize the derived global variable list (empty initially)
    derivedGlobalVariableList.clear();
}
// Backward Chaining Functions Implementation
// Search for a matching conclusion in the global conclusion list
int search_con(const string& variable) {
    if (derivedGlobalVariableList.find(variable) != derivedGlobalVariableList.end()) {
        return clauseVariableList[variable];  // Return the clause number if found
    }
    return -1;  // If not found, return -1
}

// Convert rule number to clause number
int rule_to_clause(int ruleNumber) {
    return 4 * (ruleNumber - 1) + 1;  // Assuming 4 slots per rule
}

// Update the Variable List (asks the user for values)
void update_VL(int Ci) {
    // Ask the user for values of variables starting from Ci
    for (int i = Ci; i < Ci + 4; ++i) {
        cout << "Enter value for variable " << i << ": ";
        string input;
        cin >> input;
        variableList[to_string(i)] = input;  // Store the variable in the list
    }
}

// Validate the rule based on the clause variables
void validate_Ri(int Ri, string& conclusion) {
    // Example: If conditions are met, assign the conclusion
    if (!variableList[to_string(Ri)].empty()) {
        conclusion = ruleList[Ri];
        derivedGlobalVariableList[ruleList[Ri]] = conclusion;
    }
}

// Process a variable to start backward chaining
void process(const string& variable) {
    int ruleNum = search_con(variable);
    if (ruleNum == -1) {
        cout << "Unable to find rule for variable " << variable << endl;
        return;
    }
    int Ci = rule_to_clause(ruleNum);
    update_VL(Ci);
    string conclusion;
    validate_Ri(ruleNum, conclusion);
    if (!conclusion.empty()) {
        cout << "Conclusion: " << conclusion << endl;
    } else {
        cout << "No valid conclusion found." << endl;
    }
}

// Backward Chaining algorithm to find the goal variable
void backward_chaining(const string& goalVariable) {
    cout << "Starting backward chaining for: " << goalVariable << endl;
    process(goalVariable);  // Start the backward chaining with the goal
}
// Forward Chaining for Treatment Options
void forward_chaining(const string& diagnosis) {
    cout << "\nTreatment options for " << diagnosis << ":\n";
    if (treatmentOptions.find(diagnosis) != treatmentOptions.end()) {
        for (const auto& treatment : treatmentOptions[diagnosis]) {
            cout << "- " << treatment << endl;
        }
    } else {
        cout << "No treatment options found for " << diagnosis << endl;
    }
}

// Main function
int main() {
    initialize();  // Initialize the system with symptoms, rules, and treatments

    // Step 1: Backward Chaining for Diagnosis
    string goalVariable = "Testicular Cancer";  // Example: goal variable is the diagnosis we need
    backward_chaining(goalVariable);  // Run backward chaining to determine the diagnosis
    
    // After backward chaining, check the result in the global variable list
    if (derivedGlobalVariableList.find(goalVariable) != derivedGlobalVariableList.end()) {
        cout << "Goal variable (" << goalVariable << ") found with value: "
             << derivedGlobalVariableList[goalVariable] << endl;

        // Step 2: Forward Chaining for Treatment Options
        forward_chaining(derivedGlobalVariableList[goalVariable]);  // Get treatment options for the diagnosis
    } else {
        cout << "Goal variable (" << goalVariable << ") cannot be determined." << endl;
    }
    return 0;
}
