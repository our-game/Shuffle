/*
 * Copyright (c) 2017-
 *
 * ���ļ�������XXX��Ϸ���ƣ���ֹ����һ����;��
 *
 * ʹ�÷�����
 * 1��BlackJackShuffle() ���������������ӣ�һ�������������ϴ�ƽ����
 * 2�����ߺ�������������֤��
 *		GenClientSeedForShow() ��ϴ�����ӽ���md5���ܣ�����Ϸ�����촰�������ʾ�ȶԡ�
 *		GenFinallySeed() ʹ�������б���������ϴ�����ӡ�
 *		GenRandomListBySeed()	����ϴ������������������С�
 *		Shuffle() ����ϴ���㷨�ó������˿������С�
 */

#include <string>
#include <vector>
#include <random>

static std::string sCardGraph[4] = { "��Ƭ", "÷��", "����", "����" };
static std::string sCardNumStr[14] = { "", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

int GetPokerValue(int n, int maxvalue)
{
	return (n % maxvalue) == 0 ? maxvalue : (n % maxvalue);
}

int GetPokerType(int n, int maxvalue)
{
	int type = (n % maxvalue) == 0 ? (n / maxvalue - 1) : (n / maxvalue);
	return type % 4;
}

#include "Crypto.h"

// ���ɼ��ܵĿͻ��ṩ���ӣ����ڿͻ�����ʾ
std::string GenClientSeedForShow(std::string clientSeed)
{
	return BotanCrypto::md5(clientSeed);
}

// ʹ�ÿͻ��ṩ�����Ӽ�����������������ӣ�ȫ��Ψһϴ��ID
std::string GenFinallySeed(
	std::string playerSeed1,
	std::string playerSeed2,
	std::string playerSeed3,
	std::string playerSeed4,
	std::string playerSeed5,
	std::string playerSeed6,
	std::string playerSeed7,
	std::string playerSeed8,
	std::string etSeed1,
	std::string etSeed2,
	std::string shuffleID)
{
	printf("�ͻ����ӣ�%s %s %s %s %s %s %s, %s\n",
		playerSeed1.c_str(), playerSeed2.c_str(), playerSeed3.c_str(), playerSeed4.c_str(),
		playerSeed5.c_str(), playerSeed6.c_str(), playerSeed7.c_str(), playerSeed8.c_str());

	printf("�������������ӣ�%s %s\n", etSeed1.c_str(), etSeed2.c_str());

	printf("ϴ��ID��%s\n", shuffleID.c_str());

	std::string finallySeed = playerSeed1 + playerSeed2 + playerSeed3 + playerSeed4
		+ playerSeed5 + playerSeed6 + playerSeed7 + playerSeed8
		+ etSeed1 + etSeed2 + shuffleID;

	printf("�������ӣ�%s\n\n", finallySeed.c_str());
	return finallySeed;
}

// ʹ������ϴ�����ӽ���ϴ��
std::vector<uint64_t> GenRandomListBySeed(std::string seed, int needNumCnt)
{
	std::vector<uint64_t> randNumList;
	if (needNumCnt <= 0)
		return randNumList;

	std::seed_seq tmpSeed(seed.begin(), seed.end());
	std::mt19937_64 gen(tmpSeed);
	for (int i = 0; i < needNumCnt; ++i)
		randNumList.push_back(gen());
	return std::move(randNumList);
}

/*
 *  cardCnt      ���淨�ж�������
 */
std::vector<int> Shuffle(const std::vector<uint64_t>& randomList, int cardCnt)
{
	std::vector<int> cardList;
	if (cardCnt <= 0)
		return cardList;

	for (int i = 0; i < cardCnt; ++i)
		cardList.push_back(i + 1);

	for (int i = 0; i < (int)randomList.size(); ++i)
		std::swap(cardList[i%cardCnt], cardList[randomList[i] % cardCnt]);
	return std::move(cardList);
}

/*
 *  cardMaxValue ���淨�������ֵ
 */
void PokerPrint(const std::vector<int>& cardList, int actPokerMaxValue)
{
	int cnt = 0;
	printf("���ӻ������У�\n");
	const int cardSize = (int)cardList.size();
	for (int i = 0; i < cardSize; ++i)
	{
		if (0 != i && 0 == i % 52)
			putchar('\n');

		++cnt;
		printf("%s%s ",
			sCardGraph[GetPokerType(cardList[i], actPokerMaxValue)].c_str(),
			sCardNumStr[GetPokerValue(cardList[i], actPokerMaxValue)].c_str());
	}

	putchar('\n');
}

/*
 *  finallySeed  ��������
 *  cardCnt      ���淨�ж�������
 *  cardMaxValue ���淨�������ֵ
 */
void PokerPrintShuffle(const std::string& finallySeed, int cardCnt, int cardMaxValue)
{
	if (cardCnt <= 0 || cardMaxValue <= 0)
	{
		printf("%s : %d : ��������\n", __FUNCTION__, __LINE__);
		return;
	}

	std::vector<uint64_t> randomList = GenRandomListBySeed(finallySeed, cardCnt);
	printf("������У�\n");
	for (uint64_t num : randomList)
		printf("%d ", (int)(num % cardCnt));
	printf("\n\n");

	std::vector<int> cardList = Shuffle(randomList, cardCnt);
	printf("ϴ�ƺ�����У�\n");
	for (int card : cardList)
		printf("%d ", card);
	printf("\n\n");

	PokerPrint(cardList, cardMaxValue);
}

// ����û���漰������ֵת��
void DiceShuff(const std::string& finallySeed, int diceCnt)
{
	if (diceCnt <= 0)
	{
		printf("%s : %d : ��������\n", __FUNCTION__, __LINE__);
		return;
	}

	std::vector<uint64_t> randomList = GenRandomListBySeed(finallySeed, diceCnt);
	printf("������У�\n");
	for (uint64_t num : randomList)
		printf("%d ", (int)(num % diceCnt));
	printf("\n\n");

	std::vector<int> diceList = Shuffle(randomList, diceCnt);
	printf("ϴ�ƺ�����У�\n");
	for (int dice : diceList)
		printf("%d ", dice);
	printf("\n\n");

	printf("�������ӵ����б�\n");
	for (int dice : diceList)
		printf("%d ", (dice % 6) + 1);
	putchar('\n');
}

/*
*����Q:32,��ƬQ:31,����2:30,��Ƭ2:29,����8:28,��Ƭ8:27,����4:26,��Ƭ4:25,
*����10:24,÷��10:23,����4:22��÷��4:21,����6:20,÷��6:19,����J:18,÷��J:17,
*����10:16,��Ƭ10:15,����6:14,��Ƭ6:13,����7:12,��Ƭ7:11,����9:10,÷��9:9��
*����8:8,÷��8:7,����7:6,÷��7:5,����5:4,÷��5:3,����3:2,����:1
*/
void DaXuanPrint(const std::string& finallySeed)
{
	std::vector<uint64_t> randomList = GenRandomListBySeed(finallySeed, 32);
	printf("������У�\n");
	for (uint64_t num : randomList)
		printf("%d ", (int)(num % 32));
	printf("\n\n");

	std::vector<int> cardList = Shuffle(randomList, 32);
	printf("ϴ�ƺ�����У�\n");
	for (int card : cardList)
		printf("%d ", card);
	printf("\n\n");

	static std::string cardNumStr[33] =
	{
			"",
			"����",  "����3", "÷��5", "����5", "÷��7", "����7", "÷��8",  "����8",
			"÷��9", "����9", "��Ƭ7", "����7", "��Ƭ6", "����6", "��Ƭ10", "����10",
			"÷��J", "����J", "÷��6", "����6", "÷��4", "����4", "÷��10", "����10",
			"��Ƭ4", "����4", "��Ƭ8", "����8", "��Ƭ2", "����2", "��ƬQ",  "����Q"
	};

	printf("���ӻ������У�\n");
	for (auto card : cardList)
		printf("%s ", cardNumStr[card].c_str());
	putchar('\n');
}

int main()
{
	// 1����������ϴ������
	const std::string finallySeed = GenFinallySeed("o0fGqmei", "mgFqmN5z", "", "",
		"", "", "", "",
		"", "", "6511474087809777665");

	// 2�����ݸ��ֲ�ͬ�淨�϶���ͬ����
	// 2.1��BlackJack�淨��6���ƣ��������ֵ13
	// PokerPrintShuffle(finallySeed, 312, 13);

	// 2.2�������淨��ʹ��3������
	// DiceShuff(finallySeed, 3);

	// 2.2���ټ����淨��6���ƣ��������ֵ13
	// PokerPrintShuffle(finallySeed, 312, 13);

	// 2.3�����淨��1���ƣ��������ֵ9��13
	// PokerPrintShuffle(finallySeed, 52, 9);

	// 2.4��ţţ�淨��1���ƣ��������ֵ13
	// PokerPrintShuffle(finallySeed, 52, 13);

	// 2.5�������淨����Ӧ�Ƚ�����
	DaXuanPrint(finallySeed);

	getchar();
	return 0;
}