pragma solidity >=0.7.4;

// SPDX-License-Identifier: UNLICENSED

contract PatientInfo {
    struct Patient {
        string id;
        string name;
        string contactNo;
        string treatment;
    }
    Patient[20] PatientInfoArray;
    uint256 i = 0;

    function registerPatient(
        string memory _pat_id,
        string memory _name,
        string memory _contact,
        string memory _treatment
    ) public returns (string memory) {
        Patient memory patient = Patient(_pat_id, _name, _contact, _treatment);

        if (i > 20) {
            return "Memory limit exhausted";
        } else {
            PatientInfoArray[i] = patient;
            i += 1;
            return "Patient registered successfully!";
        }
    }

    function getPatient(uint256 idx) public view returns (string memory) {
        Patient memory patient = PatientInfoArray[idx];
        return
            string(
                bytes.concat(
                    "Name: ",
                    bytes(patient.name),
                    ", Contact No.: ",
                    bytes(patient.contactNo),
                    ", Patient id: ",
                    bytes(patient.id),
                    ", Treatment: ",
                    bytes(patient.treatment)
                )
            );
    }
}
