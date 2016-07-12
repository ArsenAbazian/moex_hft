#include <stdio.h>
#include <exception>
#include <stdexcept>
#include <limits.h>
#include "FastProtocolManager.h"
#include "FastProtocolTester.h"

FastProtocolTester::FastProtocolTester()
{
}


FastProtocolTester::~FastProtocolTester()
{
}

void FastProtocolTester::TestMessageSequenceNumber() { 
	FastProtocolManager *manager = new FastProtocolManager();
	
	*((int*)(manager->Buffer())) = 0x12345678;
	int seq = manager->ReadMsgSeqNumber();

	if (manager->CurrentPos() - manager->Buffer() != 4) { 
		printf("ReadMsgSeqNumber: expected 4 but was %ld", manager->CurrentPos() - manager->Buffer());
		throw;
	}
	if (seq != 0x12345678) { 
		printf("ReadMsgSeqNumber: expected 0x12345678 but was %x", seq);
		throw;
	}

	delete manager;
}

void FastProtocolTester::TestReadInt32_Mandatory() { 
	printf("Test FastProtocolTester::TestReadInt32_Mandatory\n");
	FastProtocolManager* manager = new FastProtocolManager();

	for (int i = 0; i > -2147483630; i -= 5) {
		manager->ResetBuffer();
		manager->WriteInt32_Mandatory(i);
		manager->ResetBuffer();
		INT32 value = manager->ReadInt32_Mandatory();
		if (value != i)
			throw;
		if ((i % 1000000) == 0)
			printf("%d\n", i);
	}

	for (int i = 0; i < 0x7ffffff0; i+= 5) { 
		manager->ResetBuffer();
		manager->WriteInt32_Mandatory(i);
		manager->ResetBuffer();
		INT32 value = manager->ReadInt32_Mandatory();
		if (value != i)
			throw;
		if ((i % 1000000) == 0)
			printf("%d\n", i);
	}

	delete manager;
}

void FastProtocolTester::TestReadInt32_Optional() {
	printf("Test FastProtocolTester::TestReadInt32_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	manager->ResetBuffer();
	manager->WriteInt32_Optional(942755);
	if (manager->UsedLength() != 3)
		throw;
	if (manager->Buffer()[0] != 0x39) {
		throw std::runtime_error("buffer 0");
	}
	if (manager->Buffer()[1] != 0x45) {
		throw std::runtime_error("buffer 1");
	}
	if (manager->Buffer()[2] != 0xa4) {
		throw std::runtime_error("buffer 2");
	}

	manager->ResetBuffer();
	manager->WriteInt32_Optional(-942755);
	if (manager->UsedLength() != 3)
		throw;

	if (manager->Buffer()[0] != 0x46) {
		throw std::runtime_error("buffer 0");
	}
	if (manager->Buffer()[1] != 0x3a) {
		throw std::runtime_error("buffer 1");
	}
	if (manager->Buffer()[2] != 0xdd) {
		throw std::runtime_error("buffer 2");
	}

	manager->ResetBuffer();
	manager->Buffer()[0] = 0x46;
	manager->Buffer()[1] = 0x3a;
	manager->Buffer()[2] = 0xdd;

	int negValue = manager->ReadInt32_Optional();
	if (negValue != -942755)
		throw;
	
	delete manager;
}

void FastProtocolTester::TestReadUInt32_Optional() {
	printf("Test FastProtocolTester::TestReadUInt32_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	delete manager;
}

void FastProtocolTester::TestReadUInt32_Mandatory() {
	printf("Test FastProtocolTester::TestReadUInt32_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	for (UINT32 i = 0; i < 0xfffffff0; i += 5) {
		manager->ResetBuffer();
		manager->WriteUInt32_Mandatory(i);
		manager->ResetBuffer();
		UINT32 value = manager->ReadUInt32_Mandatory();
		if (value != i)
			throw;
		if ((i % 1000000) == 0)
			printf("%u\n", i);
	}
}

void FastProtocolTester::TestReadString_Optional() { 
	printf("Test FastProtocolTester::TestReadString_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	manager->WriteString_Optional(NULL, 0);
	if (manager->UsedLength() != 1)
		throw;
	if (manager->Buffer()[0] != 0x80)
		throw;

	manager->ResetBuffer();
	manager->WriteString_Optional((char*)"", 0);
	if (manager->UsedLength() != 2)
		throw;
	if (manager->Buffer()[0] != 0x00)
		throw;
	if (manager->Buffer()[1] != 0x80)
		throw;

	char *buffer = new char[60];
	char *buffer2 = new char[60];
	for (int i = 0; i < 60; i++) { 
		buffer[i] = (char)('A' + i);
	} 

	int length = 0;
	for (int i = 1; i < 60; i++) { 
		manager->ResetBuffer();
		manager->WriteString_Optional(buffer, i);
		if (manager->UsedLength() != i)
			throw;

		manager->ResetBuffer();
		manager->ReadString_Optional(&buffer2, &length);
		if (length != i)
			throw;
		for (int j = 0; j < i; j++) { 
			if (buffer2[j] != buffer[j])
				throw;
		}
	}

	delete manager;
}

void FastProtocolTester::TestReadString_Mandatory() {
	printf("Test FastProtocolTester::TestReadString_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	manager->WriteString_Mandatory((char*)"", 0);
	if (manager->UsedLength() != 1)
		throw;
	if (manager->Buffer()[0] != 0x80)
		throw;

	char *buffer = new char[60];
	char *buffer2 = new char[60];
	for (int i = 0; i < 60; i++) {
		buffer[i] = (char)('A' + i);
	}

	int length = 0;
	for (int i = 1; i < 60; i++) {
		manager->ResetBuffer();
		manager->WriteString_Mandatory(buffer, i);
		if (manager->UsedLength() != i)
			throw;

		manager->ResetBuffer();
		manager->ReadString_Mandatory(&buffer2, &length);
		if (length != i)
			throw;
		for (int j = 0; j < i; j++) {
			if (buffer2[j] != buffer[j])
				throw;
		}
	}

	delete manager;
}

void FastProtocolTester::TestReadByteVector_Optional() { 
	printf("Test FastProtocolTester::TestReadByteVector_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	manager->WriteByteVector_Optional(NULL, 0);
	if (manager->UsedLength() != 1)
		throw;
	if (manager->Buffer()[0] != 0x80)
		throw;

	BYTE *buffer = new BYTE[1000];
	BYTE *buffer2;
	for (int i = 0; i < 1000; i++) {
		buffer[i] = (char)('A' + i % 60);
	}

	int length = 0;
	for (int i = 0; i < 1000; i++) {
		manager->ResetBuffer();
		manager->WriteByteVector_Optional(buffer, i);
		
		manager->ResetBuffer();
		manager->ReadByteVector_Optional(&buffer2, &length);
		if (length != i)
			throw;
		for (int j = 0; j < i; j++) {
			if (buffer2[j] != buffer[j])
				throw;
		}
	}

	delete manager;
}

void FastProtocolTester::TestReadByteVector_Mandatory() {
	printf("Test FastProtocolTester::TestReadByteVector_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	BYTE *buffer = new BYTE[1000];
	BYTE *buffer2;
	for (int i = 0; i < 1000; i++) {
		buffer[i] = (char)('A' + i % 60);
	}

	int length = 0;
	for (int i = 0; i < 1000; i++) {
		manager->ResetBuffer();
		manager->WriteByteVector_Mandatory(buffer, i);

		manager->ResetBuffer();
		manager->ReadByteVector_Mandatory(&buffer2, &length);
		if (length != i)
			throw;
		for (int j = 0; j < i; j++) {
			if (buffer2[j] != buffer[j])
				throw;
		}
	}

	delete manager;
}

void FastProtocolTester::TestReadDecimal_Optional() { 
	printf("Test FastProtocolTester::TestReadDecimal_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	Decimal value = { 942755, 2 };
	manager->WriteDecimal_Optional(&value);

	if (manager->UsedLength() != 4)
		throw;
	if (!manager->CheckBuffer(new BYTE[4] { 0x83, 0x39, 0x45, 0xa3 }, 4))
		throw;

	value = { -942755, -2 };
	manager->ResetBuffer();
	manager->WriteDecimal_Optional(&value);

	if (manager->UsedLength() != 4)
		throw;
	if (!manager->CheckBuffer(new BYTE[4] { 0xfe, 0x46, 0x3a, 0xdd }, 4))
		throw;
	
	value = { -8193, -3 };
	manager->ResetBuffer();
	manager->WriteDecimal_Optional(&value);

	if (manager->UsedLength() != 4)
		throw;
	if (!manager->CheckBuffer(new BYTE[4] { 0xfd, 0x7f, 0x3f, 0xff }, 4))
		throw;

	delete manager;
}

void FastProtocolTester::TestReadDecimal_Mandatory() {
	printf("Test FastProtocolTester::TestReadDecimal_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	Decimal value = { 942755, 2 };
	manager->WriteDecimal_Mandatory(&value);

	if (manager->UsedLength() != 4)
		throw;
	if (!manager->CheckBuffer(new BYTE[4] { 0x82, 0x39, 0x45, 0xa3 }, 4))
		throw;

	value = { 9427550, 1 };
	manager->ResetBuffer();
	manager->WriteDecimal_Mandatory(&value);

	if (manager->UsedLength() != 5)
		throw;
	if (!manager->CheckBuffer(new BYTE[5] { 0x81, 0x04, 0x3f, 0x34, 0xde }, 5))
		throw;

	value = { 942755, -2 };
	manager->ResetBuffer();
	manager->WriteDecimal_Mandatory(&value);

	if (manager->UsedLength() != 4)
		throw;
	if (!manager->CheckBuffer(new BYTE[4] { 0xfe, 0x39, 0x45, 0xa3 }, 4))
		throw;
	
	delete manager;
}

void FastProtocolTester::TestReadInt64_Optional() {
	printf("Test FastProtocolTester::TestReadInt64_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();
	
	BYTE buffer[12];
	for (int i = 1; i < 10; i++) { // extended positive
		memset(buffer, 0, 12);
		for (int j = 1; j <= i; j++) { 
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 1)
				buffer[j] |= 0x40;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);
		
		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Optional();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Optional(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Optional();
		if (value2 != value)
			throw;
	}

	for (int i = 0; i < 9; i++) { // positive
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0)
				buffer[j] &= 0xbf;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Optional();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Optional(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Optional();
		if (value2 != value)
			throw;
	}

	for (int i = 1; i < 10; i++) { // extended negative
		memset(buffer, 0, 12);
		buffer[0] = 0x7f;
		for (int j = 1; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 1)
				buffer[j] &= 0xbf;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Optional();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Optional(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Optional();
		if (value2 != value)
			throw;
	}

	for (int i = 0; i < 9; i++) { // simple negative
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0) {
				buffer[j] |= 0x40;
				buffer[j] &= 0xfe;
			}
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Optional();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Optional(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Optional();
		if (value2 != value)
			throw;
	}

	delete manager;
}

void FastProtocolTester::TestReadInt64_Mandatory() {
	printf("Test FastProtocolTester::TestReadInt64_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	INT64 min = INT64_MIN + 10;

	for (INT64 i = 0; i > min; i -= 5) {
		manager->ResetBuffer();
		manager->WriteInt64_Mandatory(i);
		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		if (value != i)
			throw;
		if ((i % 1000000) == 0)
			printf("%ld\n", i);
	}

	for (INT64 i = 0; i < 0x7ffffffffffffff0; i += 5) {
		manager->ResetBuffer();
		manager->WriteInt64_Mandatory(i);
		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		if (value != i)
			throw;
		if ((i % 1000000) == 0)
			printf("%ld\n", i);
	}


	BYTE buffer[12];
	for (int i = 1; i < 10; i++) { // extended positive
		memset(buffer, 0, 12);
		for (int j = 1; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 1)
				buffer[j] |= 0x40;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Mandatory(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Mandatory();
		if (value2 != value)
			throw;
	}

	for (int i = 0; i < 9; i++) { // positive
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0)
				buffer[j] &= 0xbf;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Mandatory(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Mandatory();
		if (value2 != value)
			throw;
	}

	for (int i = 1; i < 10; i++) { // extended negative
		memset(buffer, 0, 12);
		buffer[0] = 0x7f;
		for (int j = 1; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 1)
				buffer[j] &= 0xbf;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Mandatory(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Mandatory();
		if (value2 != value)
			throw;
	}

	for (int i = 0; i < 9; i++) { // simple negative
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0)
				buffer[j] |= 0x40;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Mandatory(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Mandatory();
		if (value2 != value)
			throw;
	}

	INT64 value = 0x7fffffffffffffff;
	manager->ResetBuffer();
	manager->WriteInt64_Mandatory(value);
	manager->ResetBuffer();
	INT64 value2 = manager->ReadInt64_Mandatory();
	if (value != value2)
		throw;

	delete manager;
}

void FastProtocolTester::TestReadUInt64_Mandatory() {
	printf("Test FastProtocolTester::TestReadUInt64_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	BYTE buffer[12];

	//00 72 40 0d 6e 79 6c 21 ab
	buffer[0] = 0x01;
	buffer[1] = 0x72;
	buffer[2] = 0x0d;
	buffer[3] = 0x6e;
	buffer[4] = 0x79;
	buffer[5] = 0x6c;
	buffer[6] = 0x21;
	buffer[7] = 0xab;

	manager->ResetBuffer();
	manager->CopyToBuffer(buffer, 8);
	UINT64 v = manager->ReadUInt64_Mandatory();
	manager->ResetBuffer();
	manager->WriteUInt64_Mandatory(v);
	if (!manager->CheckBuffer(buffer, 8))
		throw;
	manager->ResetBuffer();
	UINT64 v2 = manager->ReadUInt64_Mandatory();
	if (v2 != v)
		throw;

	for (int i = 0; i < 9; i++) { // positive
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0) {
				buffer[j] &= 0xbf;
				buffer[j] |= 0x01;
			}
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		UINT64 value = manager->ReadUInt64_Mandatory();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteUInt64_Mandatory(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		UINT64 value2 = manager->ReadUInt64_Mandatory();
		if (value2 != value)
			throw;
	}

	UINT64 value = 0xffffffffffffffff;
	manager->ResetBuffer();
	manager->WriteUInt64_Mandatory(value);
	manager->ResetBuffer();
	UINT64 value2 = manager->ReadUInt64_Mandatory();
	if (value != value2)
		throw;

	delete manager;
}

void FastProtocolTester::TestReadUInt64_Optional() {
	printf("Test FastProtocolTester::TestReadUInt64_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	BYTE buffer[12];

	for (int i = 0; i < 9; i++) { // positive
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0) {
				buffer[j] &= 0xbf;
				buffer[j] |= 0x01;
			}
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		UINT64 value = manager->ReadUInt64_Optional();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteUInt64_Optional(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		UINT64 value2 = manager->ReadUInt64_Optional();
		if (value2 != value)
			throw;
	}

	UINT64 value = 0xfffffffffffffffe;
	manager->ResetBuffer();
	manager->WriteUInt64_Optional(value);
	manager->ResetBuffer();
	UINT64 value2 = manager->ReadUInt64_Optional();
	if (value != value2)
		throw;

	delete manager;
}

void FastProtocolTester::TestParsePresenceMap() {
	/*FastProtocolManager *manager = new FastProtocolManager();
	
	*(manager->Buffer()) = 0x80;
	manager->ParsePresenceMap();

	if (manager->CurrentPos() - manager->Buffer() != 1) {
		printf_s("ParsePresenceMap: expected 1 but was %d", manager->CurrentPos() - manager->Buffer());
		throw;
	}
	for (int i = 0; i < 8; i++) { 
		if (manager->PresenceMap()[i] != 0) { 
			printf_s("ParsePresenceMap: expected 0 but was %d", manager->PresenceMap()[i]);
			throw;
		}
	}
	
	for (int j = 1; j < 100;  j++) {
		manager->ResetBuffer();
		for (int l = 0; l < j - 1; l++)  {
			manager->Buffer()[l] = 0x7f;
		}
		manager->Buffer()[j - 1] = 0xff;
		manager->ParsePresenceMap();
		
		if (manager->CurrentPos() - manager->Buffer() != j) {
			printf_s("ParsePresenceMap: expected %d but was %d", j, manager->CurrentPos() - manager->Buffer());
			throw;
		}

		for (int i = 0; i < 7 * j; i++) { 
			if (manager->PresenceMap()[i] != 1) {
				printf_s("ParsePresenceMap: expected 1 but was %d", manager->PresenceMap()[i]);
				throw;
			}
		}
	}
	
	delete manager;*/
}
