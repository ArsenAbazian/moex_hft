//
// Created by root on 15.04.17.
//

#ifndef HFT_ROBOT_ORDEREDLISTMANAGER_H
#define HFT_ROBOT_ORDEREDLISTMANAGER_H

#include "../Lib/HrPointerList.h"
#include "../Fast/FastTypes.h"
#include "../Stopwatch.h"

typedef enum _ListType {
    ltSimple,
    ltSkipList
} ListType;

template <template<typename DATA> class LIST, template<typename DATA> class POINTER, typename DATA>
class OrderedListManager {
    void init_fast_srand() {
        g_seed = (Stopwatch::Default->ElapsedNanosecondsSlow() & 0xffffffff);
    }
#pragma region InsertBeforeDescendingCore
    inline POINTER<DATA>* InsertBeforeDescending1(double value, POINTER<DATA> *node, POINTER<DATA> *end) {
        while(true) {
            double valueGreater = (&(node->Data()->MDEntryPx))->Value;
            if(valueGreater < value) {
                this->m_LevelIndex = this->CalcLevel();
                return this->m_list->Insert(node);
            }
            node = node->Next();
        }
    }

    inline POINTER<DATA>* InsertBeforeDescending2(double value, POINTER<DATA> *node, POINTER<DATA> *end) {
        while(true) {
            double valueGreater = (&(node->Data()->MDEntryPx))->Value;
            if(valueGreater < value) {
                POINTER<DATA> *prev2 = node->Prev2();
                POINTER<DATA> *newNode = InsertBeforeDescending1(value, prev2, node);
                if(this->m_LevelIndex >= 2)
                    this->m_list->Insert2(prev2, newNode, node);
                return newNode;
            }
            node = node->Next2();
        }
    }

    inline POINTER<DATA>* InsertBeforeDescending3(double value, POINTER<DATA> *node, POINTER<DATA> *end) {
        while(true) {
            double valueGreater = (&(node->Data()->MDEntryPx))->Value;
            if(valueGreater < value) {
                POINTER<DATA> *prev3 = node->Prev3();
                POINTER<DATA> *newNode = InsertBeforeDescending2(value, prev3, node);
                if(this->m_LevelIndex >= 3)
                    this->m_list->Insert3(prev3, newNode, node);
                return newNode;
            }
            node = node->Next3();
        }
    }

    inline POINTER<DATA>* InsertBeforeDescending4(double value, POINTER<DATA> *node, POINTER<DATA> *end) {
        while(true) {
            double valueGreater = (&(node->Data()->MDEntryPx))->Value;
            if(valueGreater < value) {
                POINTER<DATA> *prev4 = node->Prev4();
                POINTER<DATA> *newNode = InsertBeforeDescending3(value, prev4, node);
                if(this->m_LevelIndex >= 4)
                    this->m_list->Insert4(prev4, newNode, node);
                return newNode;
            }
            node = node->Next4();
        }
    }

    inline POINTER<DATA>* InsertBeforeDescending5(double value, POINTER<DATA> *start, POINTER<DATA> *end) {
        POINTER<DATA> *node = start;
        POINTER<DATA> *newNode;
        // no items
        if (start == 0) {
            newNode = this->m_list->Add();
            return newNode;
        }
        double valueGreater = (&(start->Data()->MDEntryPx))->Value;
        // add before
        if(valueGreater < value) {
            newNode = this->m_list->Insert(start);
            if(this->m_list->Count() == 2) {
                // just connect start with end
                newNode->AllConnect(start);
                return newNode;
            }
            newNode->Connect5(start->Next5());
            newNode->Connect4(start->Next4());
            newNode->Connect3(start->Next3());
            newNode->Connect2(start->Next2());
            start->AllNext(0);
            start->AllPrev(0);
            this->m_list->InsertAfterByLevel(CalcLevel(), newNode, start);
            return newNode;
        }

        while (true) {
            valueGreater = (&(node->Data()->MDEntryPx))->Value;
            if (valueGreater < value) {
                POINTER<DATA> *prev5 = node->Prev5();
                newNode = InsertBeforeDescending4(value, prev5, node);
                if (this->m_LevelIndex == 5)
                    this->m_list->Insert5(prev5, newNode, node);
                return newNode;
            }
            if(node == end)
                break;
            node = node->Next5();
        }

        // add after
        newNode = this->m_list->Add();
        if(this->m_list->Count() == 2) {
            // just connect start with end
            start->AllConnect(newNode);
            return newNode;
        }
        end->Prev5()->Connect5(newNode);
        end->Prev4()->Connect4(newNode);
        end->Prev3()->Connect3(newNode);
        end->Prev2()->Connect2(newNode);
        end->AllPrev(0);
        end->AllNext(0);
        this->m_list->InsertBeforeByLevel(this->CalcLevel(), end, newNode);
        return newNode;
    }
#pragma endregion InsertBeforeDescendingCore

#pragma region InsertBeforeAscendingCore
    inline POINTER<DATA>* InsertBeforeAscending1(double value, POINTER<DATA> *node, POINTER<DATA> *end) {
        while(true) {
            double valueLess = (&(node->Data()->MDEntryPx))->Value;
            if(valueLess > value) {
                this->m_LevelIndex = this->CalcLevel();
                return this->m_list->Insert(node);
            }
            node = node->Next();
        }
    }

    inline POINTER<DATA>* InsertBeforeAscending2(double value, POINTER<DATA> *node, POINTER<DATA> *end) {
        while(true) {
            double valueLess = (&(node->Data()->MDEntryPx))->Value;
            if(valueLess > value) {
                POINTER<DATA> *prev2 = node->Prev2();
                POINTER<DATA> *newNode = InsertBeforeAscending1(value, prev2, node);
                if(this->m_LevelIndex >= 2)
                    this->m_list->Insert2(prev2, newNode, node);
                return newNode;
            }
            node = node->Next2();
        }
    }

    inline POINTER<DATA>* InsertBeforeAscending3(double value, POINTER<DATA> *node, POINTER<DATA> *end) {
        while(true) {
            double valueLess = (&(node->Data()->MDEntryPx))->Value;
            if(valueLess > value) {
                POINTER<DATA> *prev3 = node->Prev3();
                POINTER<DATA> *newNode = InsertBeforeAscending2(value, prev3, node);
                if(this->m_LevelIndex >= 3)
                    this->m_list->Insert3(prev3, newNode, node);
                return newNode;
            }
            node = node->Next3();
        }
    }

    inline POINTER<DATA>* InsertBeforeAscending4(double value, POINTER<DATA> *node, POINTER<DATA> *end) {
        while(true) {
            double valueLess = (&(node->Data()->MDEntryPx))->Value;
            if(valueLess > value) {
                POINTER<DATA> *prev4 = node->Prev4();
                POINTER<DATA> *newNode = InsertBeforeAscending3(value, prev4, node);
                if(this->m_LevelIndex >= 4)
                    this->m_list->Insert4(prev4, newNode, node);
                return newNode;
            }
            node = node->Next4();
        }
    }

    inline POINTER<DATA>* InsertBeforeAscending5(double value, POINTER<DATA> *start, POINTER<DATA> *end) {
        POINTER<DATA> *node = start;
        POINTER<DATA> *newNode;
        // no items
        if (start == 0) {
            newNode = this->m_list->Add();
            return newNode;
        }
        double valueLess = (&(start->Data()->MDEntryPx))->Value;
        // add before
        if(valueLess > value) {
            newNode = this->m_list->Insert(start);
            if(this->m_list->Count() == 2) {
                // just connect start with end
                newNode->AllConnect(start);
                return newNode;
            }
            newNode->Connect5(start->Next5());
            newNode->Connect4(start->Next4());
            newNode->Connect3(start->Next3());
            newNode->Connect2(start->Next2());
            start->AllNext(0);
            start->AllPrev(0);
            this->m_list->InsertAfterByLevel(CalcLevel(), newNode, start);
            return newNode;
        }

        while (true) {
            valueLess = (&(node->Data()->MDEntryPx))->Value;
            if (valueLess > value) {
                POINTER<DATA> *prev5 = node->Prev5();
                newNode = InsertBeforeAscending4(value, prev5, node);
                if (this->m_LevelIndex == 5)
                    this->m_list->Insert5(prev5, newNode, node);
                return newNode;
            }
            if(node == end)
                break;
            node = node->Next5();
        }

        // add after
        newNode = this->m_list->Add();
        if(this->m_list->Count() == 2) {
            // just connect start with end
            start->AllConnect(newNode);
            return newNode;
        }
        end->Prev5()->Connect5(newNode);
        end->Prev4()->Connect4(newNode);
        end->Prev3()->Connect3(newNode);
        end->Prev2()->Connect2(newNode);
        end->AllPrev(0);
        end->AllNext(0);
        this->m_list->InsertBeforeByLevel(this->CalcLevel(), end, newNode);
        return newNode;
    }
#pragma endregion
public:
    LIST<DATA>           *m_list;
    unsigned int         g_seed;
    int                  m_LevelIndex = 0;
    int                  m_debugLevel;
    int                  m_paddingBytes;

    // Compute a pseudorandom integer.
    // Output value in range [0, 32767]
    inline int fast_rand(void) {
        g_seed = (214013 * g_seed + 2531011);
        return (g_seed >> 16) & 0x7fff;
    }

    inline void SetDebugFastRandSeed(int seed) {
        this->g_seed = seed;
    }
    inline void SetDebugLevel(int level) {
        this->m_debugLevel = level;
    }

    OrderedListManager(LIST<DATA> *list) :
            m_debugLevel(0),
            g_seed(0),
            m_LevelIndex(0),
            m_list(0),
            m_paddingBytes(0) {
        this->m_list = list;
        this->init_fast_srand();
    }

    inline POINTER<DATA>* HrInsertBeforeDescending(Decimal *price) {
        this->m_LevelIndex = 0;
        return this->InsertBeforeDescending5(price->Calculate(), this->m_list->Start(), this->m_list->End());
    }
    inline POINTER<DATA>* HrInsertBeforeAscending(Decimal *price) {
        this->m_LevelIndex = 0;
        return this->InsertBeforeAscending5(price->Calculate(), this->m_list->Start(), this->m_list->End());
    }
    inline POINTER<DATA>* SimpleInsertBeforeDescending(Decimal *price) {
        double value = price->Calculate();
        POINTER<DATA> *node = this->m_list->Start();
        while (node != 0) {
            DATA *quote = node->Data();
            Decimal *val = &(quote->MDEntryPx);
            if (val->Value < value)
                return this->m_list->Insert(node);
            node = node->Next();
        }
        return this->m_list->Add();
    }
    inline POINTER<DATA>* SimpleInsertBeforeAscending(Decimal *price) {
        double value = price->Calculate();
        POINTER<DATA> *node = this->m_list->Start();
        while (node != 0) {
            DATA *quote = node->Data();
            Decimal *val = &(quote->MDEntryPx);
            if (val->Value > value)
                return this->m_list->Insert(node);
            node = node->Next();
        }
        return this->m_list->Add();
    }

    inline int CalcLevel() {
        //const int level2P = 32767 >> 2;
        //const int level3P = 32767 >> 3;
        //const int level4P = 32767 >> 4;
        //const int level5P = 32767 >> 6;

        const int level2P = 32767 >> 2;
        const int level3P = 32767 >> 3;
        const int level4P = 32767 >> 4;
        const int level5P = 32767 >> 5;
#ifdef TEST
        if (this->m_debugLevel != 0) {
            int res = this->m_debugLevel;
            this->m_debugLevel = 0;
            return res;
        }
#endif
        int p = fast_rand();
        if (p < level4P) {
            if (p < level5P)
                return 5;
            return 4;
        } else {
            if (p < level3P)
                return 3;
            if (p < level2P)
                return 2;
            return 1;
        }
    }
};

#endif //HFT_ROBOT_ORDEREDLISTMANAGER_H
