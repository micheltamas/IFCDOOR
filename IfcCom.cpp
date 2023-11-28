#include "Ifcread.h"

void CreateIfcDoorCom(IFCDOORRELOBJECTS* IFCS)
{
    IFCDOORCOMW IFCdoorcom;
    
    for (int i = 0; i < IFCS->IFCDOORS.size(); i++)
    {
        IFCDOOR iDoor = (IFCS->IFCDOORS)[i];
        
        std::string c1 = iDoor.p00IfcId;
        IFCdoorcom.ws_p00_IfcId = std::wstring(c1.begin(), c1.end());
        
        c1 = iDoor.p01GlobalId;
        IFCdoorcom.ws_p01_GlobalId = std::wstring(c1.begin(), c1.end());

        c1 = iDoor.p03Name;
        IFCdoorcom.ws_p02_IFCDOORName = std::wstring(c1.begin(), c1.end());

        c1 = std::to_string(iDoor.p09OverallHeight).substr(0, std::to_string(iDoor.p09OverallHeight).size() - 7);
        IFCdoorcom.ws_p03_IFCDOORHeight = std::wstring(c1.begin(), c1.end());

        c1 = std::to_string(iDoor.p10OverallWidth).substr(0, std::to_string(iDoor.p10OverallWidth).size() - 7);
        IFCdoorcom.ws_p04_IFCDOORWidth = std::wstring(c1.begin(), c1.end());

        IFCS->IFCDOORCOM.push_back(IFCdoorcom);
    }
}

void CreateIfcDoorsToList(IFCDOORRELOBJECTS* IFCS)
{
    IFCDOORSTOLISTW IFCdoorToList;

    for (int i = 0; i < IFCS->IFCRELDEFINESBYTYPES.size(); i++)
    {
        IFCRELDEFINESBYTYPE iRDT = (IFCS->IFCRELDEFINESBYTYPES)[i];
        for (int j = 0; j < iRDT.p05RelatedIFCDOORS.size(); j++)
        {
            std::string c1 = iRDT.p06RelatingIFCDOORSTYLE->p03Name;
            IFCdoorToList.ws_p00_IFCDOORSTYLEName = std::wstring(c1.begin(), c1.end());

            c1 = std::to_string(j + 1);
            IFCdoorToList.ws_p01_IFCDOORSTYLENum = std::wstring(c1.begin(), c1.end());

            c1 = iRDT.p05RelatedIFCDOORS[j]->p03Name;
            IFCdoorToList.ws_p02_IFCDOORName = std::wstring(c1.begin(), c1.end());

            c1 = std::to_string(iRDT.p05RelatedIFCDOORS[j]->p09OverallHeight).substr(0, std::to_string(iRDT.p05RelatedIFCDOORS[j]->p09OverallHeight).size() - 7);
            IFCdoorToList.ws_p03_IFCDOORHeight = std::wstring(c1.begin(), c1.end());

            c1 = std::to_string(iRDT.p05RelatedIFCDOORS[j]->p10OverallWidth).substr(0, std::to_string(iRDT.p05RelatedIFCDOORS[j]->p10OverallWidth).size() - 7);
            IFCdoorToList.ws_p04_IFCDOORWidth = std::wstring(c1.begin(), c1.end());

            c1 = iRDT.p06RelatingIFCDOORSTYLE->p09IfcDoorStyleOperationEnum;
            IFCdoorToList.ws_p05_IfcDoorStyleOperationEnum = std::wstring(c1.begin(), c1.end());


            IFCS->IFCDOORSTOLIST.push_back(IFCdoorToList);
        }
    }


}

