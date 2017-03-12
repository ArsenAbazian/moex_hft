//
// Created by root on 12.03.17.
//

#ifndef HFT_ROBOT_FORTSFEEDS_H
#define HFT_ROBOT_FORTSFEEDS_H

#include "../FeedConnection.h"

class FeedConnection_FORTS_INC : public FeedConnection {
public:
    FeedConnection_FORTS_INC(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
};

class FeedConnection_FORTS_SNAP : public FeedConnection {
public:
    FeedConnection_FORTS_SNAP(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
};

class FeedConnection_FORTS_HR : public FeedConnection {
public:
    FeedConnection_FORTS_HR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
};

class FeedConnection_FORTS_INSTR_INC : public FeedConnection {
public:
    FeedConnection_FORTS_INSTR_INC(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
};

class FeedConnection_FORTS_INSTR_SNAP : public FeedConnection {
public:
    FeedConnection_FORTS_INSTR_SNAP(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
};

#endif //HFT_ROBOT_FORTSFEEDS_H
