#include "Ifcread.h"


template <typename T>
static std::string _StartIfcRead(T * IFCType, std::string temp)
{

	int iBeg = temp.find(IFCType->ParseID) + (IFCType->ParseID).size();

	std::stringstream pString0(temp);
	std::getline(pString0, IFCType->p00IfcId, '=');
	PurgeSpaces(&IFCType->p00IfcId);

	return temp.substr(iBeg);
}

void IFCDOORRELOBJECTS::ReadIfcDoors(std::string temp)
{
	STARTREADIFCOBJ(IFCDOOR);
	
	ParseSingleProp(&sTemp, &IFCTYPE.p01GlobalId);
	ParseSingleProp(&sTemp, &IFCTYPE.p02OwnerHistory);
	ParseSingleProp(&sTemp, &IFCTYPE.p03Name);
	ParseSingleProp(&sTemp, &IFCTYPE.p04Description);
	ParseSingleProp(&sTemp, &IFCTYPE.p05ObjectType);
	ParseSingleProp(&sTemp, &IFCTYPE.p06ObjectPlacement);
	ParseSingleProp(&sTemp, &IFCTYPE.p07Representation);
	ParseSingleProp(&sTemp, &IFCTYPE.p08Tag);
	
	std::stringstream pString(sTemp);
	std::getline(pString, temp2, ',');
	IFCTYPE.p09OverallHeight = std::stod(temp2);
	std::getline(pString, temp2, ',');
	IFCTYPE.p10OverallWidth = std::stod(temp2);

	IFCDOORS.push_back(IFCTYPE);
}


void IFCDOORRELOBJECTS::ReadIfcDoorStyles(std::string temp)
{
	STARTREADIFCOBJ(IFCDOORSTYLE);

	ParseSingleProp(&sTemp, &IFCTYPE.p01GlobalId);
	ParseSingleProp(&sTemp, &IFCTYPE.p02OwnerHistory);
	ParseSingleProp(&sTemp, &IFCTYPE.p03Name);
	ParseSingleProp(&sTemp, &IFCTYPE.p04Description);
	ParseSingleProp(&sTemp, &IFCTYPE.p05ObjectType);
	ParseMultiPropBrace(&sTemp, &IFCTYPE.p06props);
	ParseMultiPropBrace(&sTemp, &IFCTYPE.p07props);
	ParseSingleProp(&sTemp, &IFCTYPE.p08Tag);
	ParseSinglePropEnum(&sTemp, &IFCTYPE.p09IfcDoorStyleOperationEnum);
	ParseSinglePropEnum(&sTemp, &IFCTYPE.p10IfcDoorStyleConstructionEnum);

	IFCDOORSTYLES.push_back(IFCTYPE);
}



void IFCDOORRELOBJECTS::ReadRelDefByTypes(std::string temp)
{

	STARTREADIFCOBJ(IFCRELDEFINESBYTYPE);

	ParseSingleProp(&sTemp, &IFCTYPE.p01GlobalId);
	ParseSingleProp(&sTemp, &IFCTYPE.p02OwnerHistory);
	ParseSingleProp(&sTemp, &IFCTYPE.p03Name);
	ParseSingleProp(&sTemp, &IFCTYPE.p04Description);

	std::vector<std::string> to_store;
	ParseMultiPropBrace(&sTemp, &to_store);
	std::string tempDSs;
	ParseSinglePropEnd(&sTemp, &tempDSs);


	for (int i = 0; i < IFCDOORSTYLES.size(); i++)
	{

		if (tempDSs == IFCDOORSTYLES[i].p00IfcId)
		{
			IFCTYPE.p06RelatingIFCDOORSTYLE = i;

			for (int k = 0; k < to_store.size(); k++)
			{
				for (int j = 0; j < IFCDOORS.size(); j++)

				{
					if (to_store[k] == IFCDOORS[j].p00IfcId)
					{
						IFCTYPE.p05RelatedIFCDOORS.push_back(j);
						IFCDOORS[j].shpDoorstyle = i;
					}
				}
			}
		}
	}

	IFCRELDEFINESBYTYPES.push_back(IFCTYPE);
}

void IFCDOORRELOBJECTS::ReadIfcMaterials(std::string temp)
{
	STARTREADIFCOBJ(IFCMATERIAL);

	ParseSinglePropEnd(&sTemp, &IFCTYPE.p01Material);
	IFCMATERIALS.push_back(IFCTYPE);
}

void ReadFromIFC(LPWSTR szFile, IFCDOORRELOBJECTS* IFCS)
{
	
	IFCS->Reset();
	std::wstring ws(szFile);
	std::string ifcFile = std::string(ws.begin(), ws.end());

	std::ifstream stData;
	stData.open(ifcFile);  //stData contains the whole IFC file at this time
	std::string temp;

	if (!stData.is_open())
		temp = "Nincs nyitva";

	// Parsing
	while (stData)
	{
		std::getline(stData, temp, '\n');
		
		if (temp.find(IFCDOOR().ParseID) != std::string::npos)
			IFCS->ReadIfcDoors(temp);
		if (temp.find(IFCDOORSTYLE().ParseID) != std::string::npos)
			IFCS->ReadIfcDoorStyles(temp);
		if (temp.find(IFCRELDEFINESBYTYPE().ParseID) != std::string::npos)
			IFCS->ReadRelDefByTypes(temp);

		if (temp.find(IFCMATERIAL().ParseID) != std::string::npos)
			IFCS->ReadIfcMaterials(temp);

	}
	//CreateIfcDoorCom(IFCS);
	CreateIfcDoorsToList(IFCS);

	stData.close();
}
