#pragma once
#include "FeedConnection.h"

class FeedChannel
{
	char id[16];
	int  m_idLogIndex;
	char name[64];
	int  m_nameLogIndex;

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

	inline bool DoWorkAtom() {
		bool res = this->orderBookIncremental->DoWorkAtom();
		res &= this->orderBookSnapshot->DoWorkAtom();
		res &= this->statisticsIncremental->DoWorkAtom();
		res &= this->statisticsSnapshot->DoWorkAtom();
		res &= this->ordersIncremental->DoWorkAtom();
		res &= this->ordersSnapshot->DoWorkAtom();
		res &= this->tradesIncremental->DoWorkAtom();
		res &= this->tradesSnapshot->DoWorkAtom();
		res &= this->instrumentReplay->DoWorkAtom();
		res &= this->instrumentStatus->DoWorkAtom();
		res &= this->historicalReplay->DoWorkAtom();

		return res;
	}
};

