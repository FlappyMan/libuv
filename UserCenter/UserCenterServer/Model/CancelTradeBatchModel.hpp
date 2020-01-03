#ifndef _CANCELTRADEBAT_MODEL_HEADER_
#define _CANCELTRADEBAT_MODEL_HEADER_

#include "../global.h"
class CCancelTradeBatchModel
{
public:
    CCancelTradeBatchModel &operator=(const CCancelTradeBatchModel &obj)
    {
        if (this != &obj)
        {
            this->ids = obj.ids;
        }
        return *this;
    }
    CCancelTradeBatchModel &operator=(UPCanceltradebatch *pkg)
    {
#warning CCancelTradeBatchModel 记得添加token
        // this->token = dynamic_cast<UPCanceltrade *>(pkg)->token();
        int iSize = dynamic_cast<UPCanceltradebatch *>(pkg)->ids_size();
        for (int iLoop = 0; iLoop < iSize; iLoop++)
        {
            int id = dynamic_cast<UPCanceltradebatch *>(pkg)->ids(iLoop);
            this->ids.push_back(id);
        }

        return *this;
    }

public:
    string token;
    list<int> ids;
};

#endif
