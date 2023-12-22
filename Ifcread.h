#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "resource.h"
#include <windows.h>
#include <Commdlg.h>
#include <list>
#include <array>
#include <map>

#define WSTR std::wstring
#define CWSTR const std::wstring
#define RETWSTR(_str) \
	std::wstring(_str.begin(), _str.end())
#define TONEWWSTR(_New_wstr,_str_to_conv) \
	std::wstring _New_wstr = std::wstring(_str_to_conv.begin(), _str_to_conv.end())
#define STARTREADIFCOBJ(_IFCTYPE) \
	_IFCTYPE IFCTYPE; \
	std::string temp2; \
	std::string sTemp = StartIfcReadAddIfcID<_IFCTYPE>(&IFCTYPE, temp)
#define ENDREADIFCOBJ(_IFCCOLLECTOR) \
	_IFCCOLLECTOR.push_back(IFCTYPE)
#define AFTERREAD(_RAT, _RAV, _RLT, _RLV, _R) \
	ReadRelAssociatesList<_RAT, _RLT>(&_RAV, &_RLV, _R, &IFCDOORS)
#define RELUNDEFINED -1
#define UNDEFINED "NEM DEFINIÁLT"
#define COLLECTORTYPE(_COLLTYPE) _COLLTYPE
#define PSET_DOORCOM_MAX 12

void PurgeSpaces(std::string* str);
void ParseSingleProp(std::string* sTemp, std::string* to_store);
void ParseSinglePropEnum(std::string* sTemp, std::string* to_store);
void ParseSinglePropEnd(std::string* sTemp, std::string* to_store);
void ParseMultiPropBrace(std::string* sTemp, std::vector<std::string>* to_store);
template <typename T> std::string StartIfcReadAddIfcID(T* IFCType, std::string temp)
{
	int iBeg = temp.find(IFCType->ParseID) + (IFCType->ParseID).size();
	std::stringstream pString0(temp);
	std::getline(pString0, IFCType->p00IfcId, '=');
	PurgeSpaces(&IFCType->p00IfcId);
	return temp.substr(iBeg);
}

typedef enum RELATIONENUMS
{
	r01_Doorstyle,
	r02_Materiallist,
	r03_PsetDoorCom,
	MAXRELATION
};


//PARENT STRUCT CONATINING IFC FILE IDEINTIFIER FOR EVERY IFC OBJECTS
struct IFCCOMMON
{
	public:
		std::string p00IfcId;
};


//STRUCTURE FOR STORING THE DATA TO BE DISPLAYED
struct IFCDOORSTOLISTW
{
	std::wstring ws_p00_IFCDOORSTYLEName;
	std::wstring ws_p01_IFCDOORSTYLENum;
	std::wstring ws_p02_IFCDOORName;
	std::wstring ws_p03_IFCDOORHeight;
	std::wstring ws_p04_IFCDOORWidth;
	std::wstring ws_p05_IfcDoorStyleOperationEnum;
	std::wstring ws_p06_IfcDoorStyleConstructionEnum;
	std::wstring ws_p07_MATERIALMaterials;
	std::array<std::wstring, 12> ws_p08_DefinedfProperties{ TEXT(UNDEFINED), TEXT(UNDEFINED), TEXT(UNDEFINED), TEXT(UNDEFINED), TEXT(UNDEFINED), TEXT(UNDEFINED), TEXT(UNDEFINED), TEXT(UNDEFINED), TEXT(UNDEFINED), TEXT(UNDEFINED), TEXT(UNDEFINED), TEXT(UNDEFINED) };
	/*
	std::wstring ws_p08_Reference; //Reference ID for this specified type in this project (e.g. type 'A-1')
	std::wstring ws_p09_FireRating; //Fire rating for this object. It is given according to the national fire safety classification.
	std::wstring ws_p10_AcousticRating; //Acoustic rating for this object. It is giving according to the national building code. It indicates the sound transmission resistance of this object by an index ration (instead of providing full sound absorbtion values).
	std::wstring ws_p11_SecurityRating; //Index based rating system indicating security level. It is giving according to the national building code.
	std::wstring ws_p12_IsExternal; //BOOL, Indication whether the element is designed for use in the exterior (TRUE) or not (FALSE). If (TRUE) it is an external element and faces the outside of the building.
	std::wstring ws_p13_Infiltration; // m3/s Infiltration flowrate of outside air for the filler object based on the area of the filler object at a pressure level of 50 Pascals. It shall be used, if the length of all joints is unknown.
	std::wstring ws_p14_ThermalTransmittance; // W/m2K Thermal transmittance coefficient (U-Value) of a material. It applies to the total door construction.
	std::wstring ws_p15_GlazingAreaFraction; //Fraction of the glazing area relative to the total area of the filling element. It shall be used, if the glazing area is not given separately for all panels within the filling element.
	std::wstring ws_p16_HandicapAccessible; //Indication that this object is designed to be accessible by the handicapped. It is giving according to the requirements of the national building code.
	std::wstring ws_p17_FireExit; //Indication whether this object is designed to serve as an exit in the case of fire (TRUE) or not (FALSE). Here it defines an exit door in accordance to the national building code.
	std::wstring ws_p18_SelfClosing; //Indication whether this object is designed to close automatically after use (TRUE) or not (FALSE).
	std::wstring ws_p19_SmokeStop; //Indication whether the object is designed to provide a smoke stop (TRUE) or not (FALSE).
	
	std::map<int, std::string> PSDC{
	{8,"Reference"},
	{9,"FireRating"},
	{10,"AcousticRating"},
	{11,"SecurityRating"},
	{12, "IsExternal"},
	{13, "Infiltration"},			// m3/s
	{14, "ThermalTransmittance"},	// W/m2K
	{15, "GlazingAreaFraction"},
	{16, "HandicapAccessible"},
	{17,"FireExit"},
	{18,"SelfClosing"},
	{19,"SmokeStop"}
	};
	*/


};
using tvIFCDOORSTOLISTW = std::vector<IFCDOORSTOLISTW>;


//IFCDOOR AND DOORSTYLE
typedef struct IFCDOORSTYLE :IFCCOMMON
{
	std::string ParseID = "IFCDOORSTYLE(";
	std::string p01GlobalId;
	std::string p02OwnerHistory;
	std::string p03Name;	
	std::string p04Description;
	std::string p05ObjectType;
	std::vector<std::string> p06props;
	std::vector<std::string>  p07props;
	std::string  p08Tag;
	std::string p09IfcDoorStyleOperationEnum;
	std::string p10IfcDoorStyleConstructionEnum;
};
using tvIFCDOORSTYLE = std::vector<IFCDOORSTYLE>;

typedef struct IFCDOOR :IFCCOMMON
{
		std::string ParseID = "IFCDOOR(";
		std::string p01GlobalId;
		std::string p02OwnerHistory;
		std::string p03Name;
		std::string p04Description;
		std::string p05ObjectType;
		std::string p06ObjectPlacement;
		std::string p07Representation;
		std::string p08Tag;
		double p09OverallHeight;
		double p10OverallWidth;

		std::array<int, MAXRELATION> relationsToList{ RELUNDEFINED ,RELUNDEFINED ,RELUNDEFINED };
};
using tvIFCDOOR = std::vector<IFCDOOR>;

typedef struct IFCRELDEFINESBYTYPE :IFCCOMMON
{
	std::string ParseID = "IFCRELDEFINESBYTYPE(";
	std::string p01GlobalId;
	std::string p02OwnerHistory;
	std::string p03Name;
	std::string p04Description;

	std::vector<std::string> p05RelatedObjects_str;
	std::vector<int> p05RelatedObjects;

	std::string p06RelatingObject_str;
	int p06RelatingObject = RELUNDEFINED;
};
using tvIFCRELDEFINESBYTYPE = std::vector<IFCRELDEFINESBYTYPE>;


//MATERIALS
typedef struct IFCRELASSOCIATESMATERIAL :IFCCOMMON
{
	std::string ParseID = "IFCRELASSOCIATESMATERIAL(";
	std::string p01GlobalId;
	std::string p02OwnerHistory;
	std::string p03Name;
	std::string p04Description;

	std::vector<std::string> p05RelatedObjects_str;
	std::vector<int> p05RelatedObjects;

	std::string p06RelatingObject_str;
	int p06RelatingObject = RELUNDEFINED;
};
using tvIFCRELASSOCIATESMATERIAL = std::vector<IFCRELASSOCIATESMATERIAL>;

typedef struct IFCMATERIAL :IFCCOMMON
{
	std::string ParseID = "IFCMATERIAL(";
	std::string p01Material;
};
using tvIFCMATERIAL = std::vector<IFCMATERIAL>;

typedef struct IFCMATERIALLIST :IFCCOMMON
{
	std::string ParseID = "IFCMATERIALLIST(";
	std::vector<int> p01RelatedObjects;

	std::string p03Name = "";

	std::string sMateriallist;
};
using tvIFCMATERIALLIST = std::vector<IFCMATERIALLIST>;


//PROPERTIES
typedef struct IFCRELDEFINESBYPROPERTIES : IFCCOMMON
{
	std::string ParseID = "IFCRELDEFINESBYPROPERTIES(";
	std::string p01GlobalId;
	std::string p02OwnerHistory;
	std::string p03Name;
	std::string p04Description;

	std::vector<std::string> p05RelatedObjects_str;
	std::vector<int> p05RelatedObjects;

	std::string p06RelatingObject_str;
	int p06RelatingObject = RELUNDEFINED;
};
using tvIFCRELDEFINESBYPROPERTIES = std::vector<IFCRELDEFINESBYPROPERTIES>;

typedef struct IFCPROPERTYSET :IFCCOMMON
{
	std::string ParseID = "IFCPROPERTYSET(";
	std::string p01GlobalId;
	std::string p02OwnerHistory;
	std::string p03Name;
	std::string p04Description;

	std::vector<std::string> p05RelatedObjects_str;
	std::vector<int> p05RelatedObjects;

	std::string sThermalTransmittance;
};
using tvIFCPROPERTYSET = std::vector<IFCPROPERTYSET>;

typedef struct IFCPROPERTYSINGLEVALUE :IFCCOMMON
{
	std::string ParseID = "IFCPROPERTYSINGLEVALUE(";
	std::string p01propertyname;
	std::string p02void;
	std::string p03propertyValue;
	std::string p04void;
};
using tvIFCPROPERTYSINGLEVALUE = std::vector<IFCPROPERTYSINGLEVALUE>;

//TEMPLATE FOR ASSOCIATIONS
template <typename T, typename U> void ReadRelAssociatesList(T* RA, U* RL, RELATIONENUMS R, tvIFCDOOR* IFCDOORS, std::string FilName = "")
{
	for (int n = 0; n < RA->size(); n++)
	{
		for (int i = 0; i < RL->size(); i++)
		{
			if ((*RA)[n].p06RelatingObject_str == (*RL)[i].p00IfcId)
			{
				(*RA)[n].p06RelatingObject = i;
			}
		}
	}

	for (int n = 0; n < RA->size(); n++)
	{
		if ((*RA)[n].p06RelatingObject == RELUNDEFINED)
			continue;
		for (int i = 0; i < RL->size(); i++)
		{

			if ((*RL)[(*RA)[n].p06RelatingObject].p00IfcId == (*RL)[i].p00IfcId)
			{
				for (int k = 0; k < (*RA)[n].p05RelatedObjects_str.size(); k++)
				{
					for (int j = 0; j < IFCDOORS->size(); j++)

					{
						
						if ((*RA)[n].p05RelatedObjects_str[k] == (*IFCDOORS)[j].p00IfcId)
						{
							if (FilName == "")
							{
								(*RA)[n].p05RelatedObjects.push_back(j);
								(*IFCDOORS)[j].relationsToList[R] = i;
							}
							else if (FilName == (*RL)[i].p03Name)
							{
								(*RA)[n].p05RelatedObjects.push_back(j);
								(*IFCDOORS)[j].relationsToList[R] = i;
							}

						}
					}
				}
			}
		}
	}
}

//MAIN DATA CONTAINER
struct IFCDOORRELOBJECTS
{
	WSTR FileName;
	//IFC OBJECTS
	tvIFCDOOR IFCDOORS;
	tvIFCRELDEFINESBYTYPE IFCRELDEFINESBYTYPES;
	tvIFCDOORSTYLE IFCDOORSTYLES;

	tvIFCRELASSOCIATESMATERIAL IFCRELASSOCIATESMATERIALS;
	tvIFCMATERIALLIST IFCMATERIALLISTS;
	tvIFCMATERIAL IFCMATERIALS;

	tvIFCRELDEFINESBYPROPERTIES IFCRELDEFINESBYPROPERTIESES;
	tvIFCPROPERTYSET IFCPROPERTYSETS;
	tvIFCPROPERTYSINGLEVALUE IFCPROPERTYSINGLEVALUES;

	//FOR UI
	tvIFCDOORSTOLISTW IFCDOORSTOLIST;


	void ReadIfcDoorStyles(std::string temp);
	void ReadIfcDoors(std::string temp);
	void ReadRelDefByTypes(std::string temp);

	void ReadIfcMateriallists(std::string temp);
	void ReadIfcMaterials(std::string temp);
	void ReadRelAssociatesMaterials(std::string temp);

	void ReadPropertySets(std::string temp);
	void ReadPropertySingleValues(std::string temp);
	void ReadRelDefinesByProperties(std::string temp);

	void AfterRead()
	{
		//ReadRelDefByTypesAfterRead();
		//ReadRelAssociatesMaterialsAfterRead();
		ReadRelAssociatesList<tvIFCRELDEFINESBYTYPE, tvIFCDOORSTYLE>(&IFCRELDEFINESBYTYPES, &IFCDOORSTYLES, r01_Doorstyle, &IFCDOORS);
		ReadRelAssociatesList<tvIFCRELASSOCIATESMATERIAL, tvIFCMATERIALLIST>(&IFCRELASSOCIATESMATERIALS, &IFCMATERIALLISTS, r02_Materiallist, &IFCDOORS);
		ReadRelAssociatesList<tvIFCRELDEFINESBYPROPERTIES, tvIFCPROPERTYSET>(&IFCRELDEFINESBYPROPERTIESES, &IFCPROPERTYSETS, r03_PsetDoorCom, &IFCDOORS, "Pset_DoorCommon");


		//AFTERREAD(tvIFCRELDEFINESBYTYPE, IFCRELDEFINESBYTYPES, tvIFCDOORSTYLE, IFCDOORSTYLES, r01_Doorstyle);
		//AFTERREAD(tvIFCRELASSOCIATESMATERIAL, IFCRELASSOCIATESMATERIALS, tvIFCMATERIALLIST, IFCMATERIALLISTS, r02_Materiallist);
		//AFTERREAD(tvIFCRELDEFINESBYPROPERTIES, IFCRELDEFINESBYPROPERTIESES, tvIFCPROPERTYSET, IFCPROPERTYSETS, r03_PsetDoorCom);
	}

	void Reset()
	{
		IFCDOORS = {};
		IFCRELDEFINESBYTYPES = {};
		IFCDOORSTYLES = {};

		IFCRELASSOCIATESMATERIALS = {};
		IFCMATERIALLISTS = {};
		IFCMATERIALS = {};

		IFCRELDEFINESBYPROPERTIESES = {};
		IFCPROPERTYSETS = {};
		IFCPROPERTYSINGLEVALUES = {};

		IFCDOORSTOLIST = {};
		

	}
};



void ReadFromIFC(LPWSTR szFile, IFCDOORRELOBJECTS* IFCS);
void CreateIfcDoorsToList(IFCDOORRELOBJECTS* IFCS);


