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

void PurgeSpaces(std::string* str);
void ParseSingleProp(std::string* sTemp, std::string* to_store);
void ParseSinglePropEnum(std::string* sTemp, std::string* to_store);
void ParseSinglePropEnd(std::string* sTemp, std::string* to_store);
void ParseMultiPropBrace(std::string* sTemp, std::vector<std::string>* to_store);

template <typename T>
T getList(std::list<T> _list, int _i) 
{
	std::list<T>::template iterator it = _list.begin();
	
	for (int i = 0; i < _i; i++) 
	{
	++it;
	}
	return *it;
}

struct IFCCOMMON
{
	public:
		std::string p00IfcId;
};


struct IFCDOORCOMW :IFCCOMMON
{
	std::wstring ws_p00_IfcId;
	std::wstring ws_p01_GlobalId;
	std::wstring ws_p02_IFCDOORName;
	std::wstring ws_p03_IFCDOORHeight;
	std::wstring ws_p04_IFCDOORWidth;
	std::wstring ws_p05_MATERIALMaterials;
	std::wstring ws_p06_IfcDoorStyleOperationEnum;
	std::wstring ws_p07_IfcDoorStyleConstructionEnum;
};



using tvIFCDOORCOMW = std::list<IFCDOORCOMW>;

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

struct IFCDOORSTYLE :IFCCOMMON
{
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

struct IFCDOOR :IFCCOMMON
{
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
		int shpDoorstyle = -1;

};

using tvIFCDOOR = std::vector<IFCDOOR>;



struct IFCRELDEFINESBYTYPE :IFCCOMMON
{
	std::string p01GlobalId;
	std::string p02OwnerHistory;
	std::string p03Name;
	std::string p04Description;
	std::vector<int> p05RelatedIFCDOORS;
	int p06RelatingIFCDOORSTYLE;
};

using tvIFCRELDEFINESBYTYPE = std::vector<IFCRELDEFINESBYTYPE>;

struct IFCRELASSOCIATESMATERIAL :IFCCOMMON
{
	std::string p01GlobalId;
	std::string p02OwnerHistory;
	std::string p03Name;
	std::string p04Description;
	std::vector<std::string> p05RelatedObjects;
	int p06RelatingType;
};

using tvIFCRELASSOCIATESMATERIAL = std::vector<IFCRELASSOCIATESMATERIAL>;

struct IFCMATERIAL :IFCCOMMON
{
	std::string p01Material;
};

using tvIFCMATERIAL = std::vector<IFCMATERIAL>;

struct IFCMATERIALLIST :IFCCOMMON
{
	std::vector<std::string> p01RelatedObjects;
};

using tvIFCMATERIALLIST = std::vector<IFCMATERIALLIST>;

enum IFCDOORRELOBJECTS_ENUM
{
	e_IFCDOORS = 0,
	e_IFCRELDEFINESBYTYPES,
	e_IFCDOORSTYLES,
	e_IFCRELASSOCIATESMATERIAL,
	e_IFCMATERIALLIST,
	e_IFCMATERIALS,
	e_IFCDOORCOM,
	e_IFCDOORSTOLIST,
};

struct IFCDOORRELOBJECTS
{
	
	tvIFCDOOR IFCDOORS;
	tvIFCRELDEFINESBYTYPE IFCRELDEFINESBYTYPES;
	tvIFCDOORSTYLE IFCDOORSTYLES;
	tvIFCRELASSOCIATESMATERIAL IFCRELASSOCIATESMATERIAL;
	tvIFCMATERIALLIST IFCMATERIALLIST;
	tvIFCMATERIAL IFCMATERIALS;
	tvIFCDOORCOMW IFCDOORCOM;
	tvIFCDOORSTOLISTW IFCDOORSTOLIST;


	std::string ParseID_IFCDOOR = "IFCDOOR(";
	std::string ParseID_IFCRELDEFINESBYTYPE = "IFCRELDEFINESBYTYPE(";
	std::string ParseID_IFCDOORSTYLE = "IFCDOORSTYLE(";
	std::string ParseID_IFCRELASSOCIATESMATERIAL = "IFCRELASSOCIATESMATERIAL(";
	std::string ParseID_IFCMATERIALLIST = "IFCMATERIALLIST(";
	std::string ParseID_IFCMATERIAL = "IFCMATERIAL(";

	void ReadIfcDoorStyles(std::string temp);
	void ReadIfcDoors(std::string temp);
	void ReadIfcMaterials(std::string temp);

	void ReadRelDefByTypes(std::string temp);
	void Reset()
	{
		IFCDOORS = {};
		IFCRELDEFINESBYTYPES = {};
		IFCDOORSTYLES = {};
		IFCRELASSOCIATESMATERIAL = {};
		IFCMATERIALLIST = {};
		IFCMATERIALS = {};
		IFCDOORCOM = {};
		IFCDOORSTOLIST = {};
	}
};



void ReadFromIFC(LPWSTR szFile, IFCDOORRELOBJECTS* IFCS);
void CreateIfcDoorCom(IFCDOORRELOBJECTS * IFCS);
void CreateIfcDoorsToList(IFCDOORRELOBJECTS* IFCS);
