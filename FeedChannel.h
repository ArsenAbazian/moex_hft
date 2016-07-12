#pragma once
#include "FeedConnection.h"

class FeedChannel
{
	char id[16];
	char name[64];

	FeedConnection *orderBookIncremental;
	FeedConnection *orderBookSnapshot;
	FeedConnection *statisticsIncremental;
	FeedConnection *statisticsSnapshot;
	FeedConnection *ordersIncremental;
	FeedConnection *ordersSnapshot;
	FeedConnection *tradesIncremental;
	FeedConnection *tradesSnapshot;
	FeedConnection *instrumentReplay;
	FeedConnection *instrumentStatus;
	FeedConnection *historicalReplay;

public:
	FeedChannel(const char *id, const char *name);
	~FeedChannel();

	void SetConnection(FeedConnection *conn);
	const char* Id() { return this->id; }
	const char* Name() { return this->name; }

	bool Connect(FeedConnection *conn);
	bool Disconnect(FeedConnection *conn);
	bool Connect();
	bool Disconnect();
	bool Logon(FeedConnection *conn);
	bool Logout(FeedConnection *conn);
	bool Logon();
	bool Logout();
};

