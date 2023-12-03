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
#define RELUNDEFINED -1

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

struct IFCCOMMON
{
	public:
		std::string p00IfcId;
};


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
};
using tvIFCDOORSTOLISTW = std::vector<IFCDOORSTOLISTW>;

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
		int shpDoorstyle = RELUNDEFINED;
		int shpMateriallist = RELUNDEFINED;
};
using tvIFCDOOR = std::vector<IFCDOOR>;

typedef struct IFCRELDEFINESBYTYPE :IFCCOMMON
{
	std::string ParseID = "IFCRELDEFINESBYTYPE(";
	std::string p01GlobalId;
	std::string p02OwnerHistory;
	std::string p03Name;
	std::string p04Description;

	std::vector<std::string> p05RelatedObjects;
	std::vector<int> p05RelatedDoors;

	std::string p06RelatingType_str;
	int p06RelatingType = RELUNDEFINED;
};
using tvIFCRELDEFINESBYTYPE = std::vector<IFCRELDEFINESBYTYPE>;

typedef struct IFCRELASSOCIATESMATERIAL :IFCCOMMON
{
	std::string ParseID = "IFCRELASSOCIATESMATERIAL(";
	std::string p01GlobalId;
	std::string p02OwnerHistory;
	std::string p03Name;
	std::string p04Description;

	std::vector<std::string> p05RelatedObjects;
	std::vector<int> p05RelatedDoors;

	std::string p06RelatingType_str;
	int p06RelatingType = RELUNDEFINED;
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

	std::string sMateriallist;
};
using tvIFCMATERIALLIST = std::vector<IFCMATERIALLIST>;


struct IFCDOORRELOBJECTS
{
	WSTR FileName;
	
	tvIFCDOOR IFCDOORS;
	tvIFCRELDEFINESBYTYPE IFCRELDEFINESBYTYPES;
	tvIFCDOORSTYLE IFCDOORSTYLES;
	tvIFCRELASSOCIATESMATERIAL IFCRELASSOCIATESMATERIALS;
	tvIFCMATERIALLIST IFCMATERIALLISTS;
	tvIFCMATERIAL IFCMATERIALS;
	tvIFCDOORSTOLISTW IFCDOORSTOLIST;


	void ReadIfcDoorStyles(std::string temp);
	void ReadIfcDoors(std::string temp);
	void ReadIfcMateriallists(std::string temp);
	void ReadIfcMaterials(std::string temp);

	void ReadRelDefByTypes(std::string temp);
	void ReadRelDefByTypesAfterRead();

	void ReadRelAssociatesMaterials(std::string temp);
	void ReadRelAssociatesMaterialsAfterRead();

	void Reset()
	{
		IFCDOORS = {};
		IFCRELDEFINESBYTYPES = {};
		IFCDOORSTYLES = {};
		IFCRELASSOCIATESMATERIALS = {};
		IFCMATERIALLISTS = {};
		IFCMATERIALS = {};
		IFCDOORSTOLIST = {};
	}
};



void ReadFromIFC(LPWSTR szFile, IFCDOORRELOBJECTS* IFCS);
void CreateIfcDoorsToList(IFCDOORRELOBJECTS* IFCS);
