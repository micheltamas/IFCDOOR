#include "Ifcread.h"


void CreateIfcDoorsToList(IFCDOORRELOBJECTS* IFCS)
{
    IFCDOORSTOLISTW IFCdoorToList;
    
    for (int i = 0; i < IFCS->IFCDOORS.size(); i++)
    {
        
        IFCDOOR ifd = (IFCS->IFCDOORS)[i];

            std::string c1 = ifd.shpDoorstyle != RELUNDEFINED ? (IFCS->IFCDOORSTYLES)[ifd.shpDoorstyle].p03Name : "NOTDEFINED";
            IFCdoorToList.ws_p00_IFCDOORSTYLEName = RETWSTR(c1);

            c1 = "-";
            IFCdoorToList.ws_p01_IFCDOORSTYLENum = RETWSTR(c1);

            c1 = ifd.p03Name;
            IFCdoorToList.ws_p02_IFCDOORName = RETWSTR(c1);

            c1 = std::to_string(ifd.p09OverallHeight).substr(0, std::to_string(ifd.p09OverallHeight).size() - 7);
            IFCdoorToList.ws_p03_IFCDOORHeight = RETWSTR(c1);

            c1 = std::to_string(ifd.p10OverallWidth).substr(0, std::to_string(ifd.p10OverallWidth).size() - 7);
            IFCdoorToList.ws_p04_IFCDOORWidth = RETWSTR(c1);

            c1 = ifd.shpDoorstyle != RELUNDEFINED ? (IFCS->IFCDOORSTYLES)[ifd.shpDoorstyle].p09IfcDoorStyleOperationEnum : "NOTDEFINED";
            IFCdoorToList.ws_p05_IfcDoorStyleOperationEnum = RETWSTR(c1);

            if (ifd.shpMateriallist != RELUNDEFINED)
            {
                c1 = "(";
                std::vector<int> vM = IFCS->IFCMATERIALLISTS[ifd.shpMateriallist].p01RelatedObjects;
                for (int i = 0; i < vM.size() ;i++)
                {
                    c1 = i < vM.size()-1 ? c1 + IFCS->IFCMATERIALS[vM[i]].p01Material + "; " : c1 + IFCS->IFCMATERIALS[vM[i]].p01Material + ")";
                }
            }
            else
                c1 = "NOTDEFINED";
            IFCdoorToList.ws_p07_MATERIALMaterials = RETWSTR(c1);


            IFCS->IFCDOORSTOLIST.push_back(IFCdoorToList);
        
    }
    

}

