#include "Ifcread.h"


static std::wstring _Parse_Pset_Doorcom(std::string PID, std::string temp)
{
    if (temp == "$")
        return TEXT(UNDEFINED);
    
    PID = PID + "(";
    int iBeg = temp.find(PID) + (PID).size();
    temp = temp.substr(iBeg);
    std::stringstream pString0(temp);
    std::getline(pString0, temp, ')');
    return RETWSTR(temp);
}

void CreateIfcDoorsToList(IFCDOORRELOBJECTS* IFCS)
{
    IFCDOORSTOLISTW IFCdoorToList;
    
    for (int i = 0; i < IFCS->IFCDOORS.size(); i++)
    {
        std::map<int, std::string> PSDC{
        {0,"Reference"},
        {1,"FireRating"},
        {2,"AcousticRating"},
        {3,"SecurityRating"},
        {4, "IsExternal"},
        {5, "Infiltration"},
        {6, "ThermalTransmittance"},
        {7, "GlazingAreaFraction"},
        {8, "HandicapAccessible"},
        {9,"FireExit"},
        {10,"SelfClosing"},
        {11,"SmokeStop"}
        };

        IFCDOOR ifd = (IFCS->IFCDOORS)[i];

            std::string c1 = ifd.relationsToList[r01_Doorstyle] != RELUNDEFINED ? (IFCS->IFCDOORSTYLES)[ifd.relationsToList[r01_Doorstyle]].p03Name : UNDEFINED;
            IFCdoorToList.ws_p00_IFCDOORSTYLEName = RETWSTR(c1);

            c1 = "-";
            IFCdoorToList.ws_p01_IFCDOORSTYLENum = RETWSTR(c1);

            c1 = ifd.p03Name;
            IFCdoorToList.ws_p02_IFCDOORName = RETWSTR(c1);

            c1 = std::to_string(ifd.p09OverallHeight).substr(0, std::to_string(ifd.p09OverallHeight).size() - 7);
            IFCdoorToList.ws_p03_IFCDOORHeight = RETWSTR(c1);

            c1 = std::to_string(ifd.p10OverallWidth).substr(0, std::to_string(ifd.p10OverallWidth).size() - 7);
            IFCdoorToList.ws_p04_IFCDOORWidth = RETWSTR(c1);

            c1 = ifd.relationsToList[r01_Doorstyle] != RELUNDEFINED ? (IFCS->IFCDOORSTYLES)[ifd.relationsToList[r01_Doorstyle]].p09IfcDoorStyleOperationEnum : UNDEFINED;
            IFCdoorToList.ws_p05_IfcDoorStyleOperationEnum = RETWSTR(c1);

            if (ifd.relationsToList[r02_Materiallist] != RELUNDEFINED)
            {
                c1 = "(";
                std::vector<int> vM = IFCS->IFCMATERIALLISTS[ifd.relationsToList[r02_Materiallist]].p01RelatedObjects;
                for (int j = 0; j < vM.size() ;j++)
                {
                    c1 = j < vM.size()-1 ? c1 + IFCS->IFCMATERIALS[vM[j]].p01Material + "; " : c1 + IFCS->IFCMATERIALS[vM[j]].p01Material + ")";
                }
            }
            else
                c1 = UNDEFINED;
            IFCdoorToList.ws_p07_MATERIALMaterials = RETWSTR(c1);

            if (ifd.relationsToList[r03_PsetDoorCom] != RELUNDEFINED)
            {
                
                std::vector<int> vM = IFCS->IFCPROPERTYSETS[ifd.relationsToList[r03_PsetDoorCom]].p05RelatedObjects;
                for (int n = 0; n < PSET_DOORCOM_MAX; n++)
                {
                    for (int j = 0; j < vM.size(); j++)
                    {
                        if (IFCS->IFCPROPERTYSINGLEVALUES[vM[j]].p01propertyname == PSDC[n])
                        {
                            switch (n)
                            {
                            
                            case 0:
                            {
                                IFCdoorToList.ws_p08_DefinedfProperties[n] = _Parse_Pset_Doorcom("IFCIDENTIFIER", IFCS->IFCPROPERTYSINGLEVALUES[vM[j]].p03propertyValue);
                                break;
                            }
                            case 1:
                            case 2:
                            case 3:
                            {
                                IFCdoorToList.ws_p08_DefinedfProperties[n] = _Parse_Pset_Doorcom("IFCLABEL", IFCS->IFCPROPERTYSINGLEVALUES[vM[j]].p03propertyValue);
                                break;
                            }
                            
                            case 4:
                                {
                                    if (IFCS->IFCPROPERTYSINGLEVALUES[vM[j]].p03propertyValue == "IFCBOOLEAN(.T.)")
                                        IFCdoorToList.ws_p08_DefinedfProperties[n] = TEXT("IGEN");
                                    else
                                        IFCdoorToList.ws_p08_DefinedfProperties[n] = TEXT("NEM");
                                    break;
                                }
                            case 5:
                            {
                                IFCdoorToList.ws_p08_DefinedfProperties[n] = _Parse_Pset_Doorcom("IFCVOLUMETRICFLOWRATEMEASURE", IFCS->IFCPROPERTYSINGLEVALUES[vM[j]].p03propertyValue);
                                break;
                            }
                            case 6:
                            {
                                IFCdoorToList.ws_p08_DefinedfProperties[n] = _Parse_Pset_Doorcom("IFCTHERMALTRANSMITTANCEMEASURE", IFCS->IFCPROPERTYSINGLEVALUES[vM[j]].p03propertyValue);
                                break;
                            }
                            case 7:
                            {
                                IFCdoorToList.ws_p08_DefinedfProperties[n] = _Parse_Pset_Doorcom("IFCPOSITIVERATIOMEASURE", IFCS->IFCPROPERTYSINGLEVALUES[vM[j]].p03propertyValue);
                                break;
                            }
 
                            case 8:
                            case 9:
                            case 10:
                            case 11:
                                {
                                    if (IFCS->IFCPROPERTYSINGLEVALUES[vM[j]].p03propertyValue == "IFCBOOLEAN(.T.)")
                                        IFCdoorToList.ws_p08_DefinedfProperties[n] = TEXT("IGEN");
                                    else
                                        IFCdoorToList.ws_p08_DefinedfProperties[n] = TEXT("NEM");
                                    break;
                                }
                            default:
                                IFCdoorToList.ws_p08_DefinedfProperties[n] = RETWSTR(IFCS->IFCPROPERTYSINGLEVALUES[vM[j]].p03propertyValue);
                            }
                        }
                    }

                }

            }



            IFCS->IFCDOORSTOLIST.push_back(IFCdoorToList);
        
    }
    

}

