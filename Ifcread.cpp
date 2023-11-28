#include "Ifcread.h"



void IFCDOORRELOBJECTS::ReadIfcDoors(std::string temp)
{
	
	IFCDOOR iDoor;
	std::string temp2;

	int iBeg = temp.find(ParseID_IFCDOOR) + (ParseID_IFCDOOR).size();

	std::stringstream pString0(temp);
	std::getline(pString0, iDoor.p00IfcId, '=');

	std::string sTemp(temp.substr(iBeg));
	
	ParseSingleProp(&sTemp, &iDoor.p01GlobalId);
	ParseSingleProp(&sTemp, &iDoor.p02OwnerHistory);
	ParseSingleProp(&sTemp, &iDoor.p03Name);
	ParseSingleProp(&sTemp, &iDoor.p04Description);
	ParseSingleProp(&sTemp, &iDoor.p05ObjectType);
	ParseSingleProp(&sTemp, &iDoor.p06ObjectPlacement);
	ParseSingleProp(&sTemp, &iDoor.p07Representation);
	ParseSingleProp(&sTemp, &iDoor.p08Tag);
	
	std::stringstream pString(sTemp);
	std::getline(pString, temp2, ',');
	iDoor.p09OverallHeight = std::stod(temp2);
	std::getline(pString, temp2, ',');
	iDoor.p10OverallWidth = std::stod(temp2);

	IFCDOORS.push_back(iDoor);
}


void IFCDOORRELOBJECTS::ReadIfcDoorStyles(std::string temp)
{

	IFCDOORSTYLE iDS;
	std::string temp2;
	int iBeg = temp.find(ParseID_IFCDOORSTYLE) + (ParseID_IFCDOORSTYLE).size();

	std::stringstream pString0(temp);
	std::getline(pString0, iDS.p00IfcId, '=');

	std::string sTemp(temp.substr(iBeg));

	ParseSingleProp(&sTemp, &iDS.p01GlobalId);
	ParseSingleProp(&sTemp, &iDS.p02OwnerHistory);
	ParseSingleProp(&sTemp, &iDS.p03Name);
	ParseSingleProp(&sTemp, &iDS.p04Description);
	ParseSingleProp(&sTemp, &iDS.p05ObjectType);
	ParseMultiPropBrace(&sTemp, &iDS.p06props);
	ParseMultiPropBrace(&sTemp, &iDS.p07props);
	ParseSingleProp(&sTemp, &iDS.p08Tag);
	ParseSinglePropEnum(&sTemp, &iDS.p09IfcDoorStyleOperationEnum);
	ParseSinglePropEnum(&sTemp, &iDS.p10IfcDoorStyleConstructionEnum);

	IFCDOORSTYLES.push_back(iDS);
}

void IFCDOORRELOBJECTS::ReadRelDefByTypes(std::string temp)
{

	IFCRELDEFINESBYTYPE iRelT;
	std::string temp2;
	int iBeg = temp.find(ParseID_IFCRELDEFINESBYTYPE) + (ParseID_IFCRELDEFINESBYTYPE).size();

	std::stringstream pString0(temp);
	std::getline(pString0, iRelT.p00IfcId, '=');

	std::string sTemp(temp.substr(iBeg));

	ParseSingleProp(&sTemp, &iRelT.p01GlobalId);
	ParseSingleProp(&sTemp, &iRelT.p02OwnerHistory);
	ParseSingleProp(&sTemp, &iRelT.p03Name);
	ParseSingleProp(&sTemp, &iRelT.p04Description);

	std::vector<std::string> to_store;
	ParseMultiPropBrace(&sTemp, &to_store);
	std::string tempDSs;
	ParseSinglePropEnd(&sTemp, &tempDSs);


	for (int i = 0; i < IFCDOORSTYLES.size(); i++)
	{

		if (tempDSs == IFCDOORSTYLES[i].p00IfcId)
		{
			iRelT.p06RelatingIFCDOORSTYLE = &IFCDOORSTYLES[i];

			for (int k = 0; k < to_store.size(); k++)
			{
				for (int j = 0; j < IFCDOORS.size(); j++)

				{
					if (to_store[k] == IFCDOORS[j].p00IfcId)
						iRelT.p05RelatedIFCDOORS.push_back(&IFCDOORS[j]);
				}
			}
		}
	}

	IFCRELDEFINESBYTYPES.push_back(iRelT);
}

void IFCDOORRELOBJECTS::ReadIfcMaterials(std::string temp)
{
	IFCMATERIAL iMat;

	std::string temp2;
	int iBeg = temp.find(ParseID_IFCMATERIAL) + (ParseID_IFCMATERIAL).size();
	
	std::stringstream pString0(temp);
	std::getline(pString0, iMat.p00IfcId, '=');

	std::string sTemp(temp.substr(iBeg));

	ParseSinglePropEnd(&sTemp, &iMat.p01Material);

	IFCMATERIALS.push_back(iMat);
}

void ReadFromIFC(LPWSTR szFile, IFCDOORRELOBJECTS* IFCS)
{

	*IFCS = {};
	std::wstring ws(szFile);
	std::string ifcFile = std::string(ws.begin(), ws.end());

	std::ifstream stData;
	stData.open(ifcFile);
	std::string temp;

	if (!stData.is_open())
		temp = "Nincs nyitva";

	while (stData)
	{
		std::getline(stData, temp, '\n');

		if (temp.find(IFCS->ParseID_IFCDOOR) != std::string::npos)
			IFCS->ReadIfcDoors(temp);
		if (temp.find(IFCS->ParseID_IFCDOORSTYLE) != std::string::npos)
			IFCS->ReadIfcDoorStyles(temp);
		if (temp.find(IFCS->ParseID_IFCRELDEFINESBYTYPE) != std::string::npos)
			IFCS->ReadRelDefByTypes(temp);

		if (temp.find(IFCS->ParseID_IFCMATERIAL) != std::string::npos)
			IFCS->ReadIfcMaterials(temp);

	}
	//CreateIfcDoorCom(IFCS);
	CreateIfcDoorsToList(IFCS);

	stData.close();
}
