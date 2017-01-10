#pragma once

static const char*	FundMarketSenderComputerId = "MU9033700003";
static const char*  FundMarketPassword = " ";

static const char*  HistoricalReplayTargetComputerId = "MOEX";
static const char*	HistoricalReplaySenderComputerId = "MU9033700003";
static const char*  HistoricalReplayUserName = "user0";
static const int    HistoricalReplayUserNameLength = 5;
static const char*  HistoricalReplayPassword = "pass0";
static int          HistoricalReplayPasswordLength = 5;

static const char*  FundMarketTradeName = "TEST Equities MFIX Trade";
static const char*	FundMarketTradeServerAddress = "91.208.232.200";
static const int	FundMarketTradeServerPort = 9120;
static const char*	FundMarketTradeTargetComputerId = "MFIXTradeID";
static const char*  FundMarketTradeASTSServerName = "INET_GATEWAY";

static const char*  FundMarketTradeCaptureName = "TEST Equities MFIX Trade Capture";
static const char*	FundMarketTradeCaptureServerAddress = "91.208.232.200";
static const int	FundMarketTradeCaptureServerPort = 9121;
static const char*	FundMarketTradeCaptureTargetComputerId = "MFIXTradeCaptureID";
static const char*  FundMarketTradeCaptureASTSServerName = "INET_GATEWAY";

static const char*  FundMarketTradeDropCopyName = "TEST Equities Drop Copy";
static const char*	FundMarketTradeDropCopyServerAddress = "91.208.232.200";
static const int	FundMarketTradeDropCopyServerPort = 9213;
static const char*	FundMarketTradeDropCopyTargetComputerId = "MFIXDropCopyID";
static const char*  FundMarketTradeDropCopyASTSServerName = "INET_GATEWAY";


static const char*	CurrencyMarketSenderComputerId = "MD9022400003";
static const char*  CurrencyMarketPassword = " ";

static const char*  CurrencyMarketTradeName = "TEST FX MFIX Trade";
static const char*	CurrencyMarketTradeServerAddress = "91.208.232.200";
static const int	CurrencyMarketTradeServerPort = 9212;
static const char*	CurrencyMarketTradeTargetComputerId = "MFIXTradeIDCurr";
static const char*  CurrencyMarketTradeASTSServerName = "INET_GATEWAY";

static const char*  CurrencyMarketTradeCaptureName = "TEST FX MFIX Trade Capture";
static const char*	CurrencyMarketTradeCaptureServerAddress = "91.208.232.200";
static const int	CurrencyMarketTradeCaptureServerPort = 9214;
static const char*	CurrencyMarketTradeCaptureTargetComputerId = "MFIXTradeCaptureIDCurr";
static const char*  CurrencyMarketTradeCaptureASTSServerName = "INET_GATEWAY";

static const char*  CurrencyMarketTradeDropCopyName = "TEST FX Drop Copy";
static const char*	CurrencyMarketTradeDropCopyServerAddress = "91.208.232.200";
static const int	CurrencyMarketTradeDropCopyeServerPort = 9211;
static const char*	CurrencyMarketTradeDropCopyTargetComputerId = "MFIXDropCopyCurrID";
static const char*  CurrencyMarketTradeDropCopyASTSServerName = "INET_GATEWAY";

static bool         EnableLogOutToConsole = true;
