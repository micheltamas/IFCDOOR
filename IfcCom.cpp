#include "Ifcread.h"


void CreateIfcDoorsToList(IFCDOORRELOBJECTS* IFCS)
{
    IFCDOORSTOLISTW IFCdoorToList;
    
    for (int i = 0; i < IFCS->IFCDOORS.size(); i++)
    {
        
        IFCDOOR ifd = (IFCS->IFCDOORS)[i];

            std::string c1 = ifd.shpDoorstyle != -1 ? (IFCS->IFCDOORSTYLES)[ifd.shpDoorstyle].p03Name : "-";
            IFCdoorToList.ws_p00_IFCDOORSTYLEName = RETWSTR(c1);

            c1 = "-";
            IFCdoorToList.ws_p01_IFCDOORSTYLENum = RETWSTR(c1);

            c1 = ifd.p03Name;
            IFCdoorToList.ws_p02_IFCDOORName = RETWSTR(c1);

            c1 = std::to_string(ifd.p09OverallHeight).substr(0, std::to_string(ifd.p09OverallHeight).size() - 7);
            IFCdoorToList.ws_p03_IFCDOORHeight = RETWSTR(c1);

            c1 = std::to_string(ifd.p10OverallWidth).substr(0, std::to_string(ifd.p10OverallWidth).size() - 7);
            IFCdoorToList.ws_p04_IFCDOORWidth = RETWSTR(c1);

            c1 = ifd.shpDoorstyle != -1 ? (IFCS->IFCDOORSTYLES)[ifd.shpDoorstyle].p09IfcDoorStyleOperationEnum : "NOTDEFINED";
            IFCdoorToList.ws_p05_IfcDoorStyleOperationEnum = RETWSTR(c1);


            IFCS->IFCDOORSTOLIST.push_back(IFCdoorToList);
        
    }
    

}

