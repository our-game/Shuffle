/*
 * Copyright (c) 2017-
 *
 * 该文件仅限于XXX游戏验牌，禁止其它一切用途。
 *
 * 使用方法：
 * 1，BlackJackShuffle() 函数接收所有种子，一次性运算出最终洗牌结果。
 * 2，工具函数，方便逐步验证：
 *		GenClientSeedForShow() 将洗牌种子进行md5加密，与游戏中聊天窗口相关显示比对。
 *		GenFinallySeed() 使用种子列表生成最终洗牌种子。
 *		GenRandomListBySeed()	根据洗牌种子生成随机数序列。
 *		Shuffle() 交换洗牌算法得出最终扑克牌序列。
 */

#include <string>
#include <vector>
#include <random>

static std::string sCardGraph[4] = { "方片", "梅花", "红桃", "黑桃" };
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

// 生成加密的客户提供种子，用于客户端显示
std::string GenClientSeedForShow(std::string clientSeed)
{
	return BotanCrypto::md5(clientSeed);
}

// 使用客户提供的种子及区块链返回随机种子，全局唯一洗牌ID
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
	printf("客户种子：%s %s %s %s %s %s %s, %s\n",
		playerSeed1.c_str(), playerSeed2.c_str(), playerSeed3.c_str(), playerSeed4.c_str(),
		playerSeed5.c_str(), playerSeed6.c_str(), playerSeed7.c_str(), playerSeed8.c_str());

	printf("区块链生成种子：%s %s\n", etSeed1.c_str(), etSeed2.c_str());

	printf("洗牌ID：%s\n", shuffleID.c_str());

	std::string finallySeed = playerSeed1 + playerSeed2 + playerSeed3 + playerSeed4
		+ playerSeed5 + playerSeed6 + playerSeed7 + playerSeed8
		+ etSeed1 + etSeed2 + shuffleID;

	printf("最终种子：%s\n\n", finallySeed.c_str());
	return finallySeed;
}

// 使用最终洗牌种子进行洗牌
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
 *  cardCnt      该玩法有多少张牌
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
 *  cardMaxValue 该玩法最大牌面值
 */
void PokerPrint(const std::vector<int>& cardList, int actPokerMaxValue)
{
	int cnt = 0;
	printf("可视化牌序列：\n");
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
 *  finallySeed  最终种子
 *  cardCnt      该玩法有多少张牌
 *  cardMaxValue 该玩法最大牌面值
 */
void PokerPrintShuffle(const std::string& finallySeed, int cardCnt, int cardMaxValue)
{
	if (cardCnt <= 0 || cardMaxValue <= 0)
	{
		printf("%s : %d : 参数错误\n", __FUNCTION__, __LINE__);
		return;
	}

	std::vector<uint64_t> randomList = GenRandomListBySeed(finallySeed, cardCnt);
	printf("随机序列：\n");
	for (uint64_t num : randomList)
		printf("%d ", (int)(num % cardCnt));
	printf("\n\n");

	std::vector<int> cardList = Shuffle(randomList, cardCnt);
	printf("洗牌后的序列：\n");
	for (int card : cardList)
		printf("%d ", card);
	printf("\n\n");

	PokerPrint(cardList, cardMaxValue);
}

// 骰子没有涉及到牌面值转换
void DiceShuff(const std::string& finallySeed, int diceCnt)
{
	if (diceCnt <= 0)
	{
		printf("%s : %d : 参数错误\n", __FUNCTION__, __LINE__);
		return;
	}

	std::vector<uint64_t> randomList = GenRandomListBySeed(finallySeed, diceCnt);
	printf("随机序列：\n");
	for (uint64_t num : randomList)
		printf("%d ", (int)(num % diceCnt));
	printf("\n\n");

	std::vector<int> diceList = Shuffle(randomList, diceCnt);
	printf("洗牌后的序列：\n");
	for (int dice : diceList)
		printf("%d ", dice);
	printf("\n\n");

	printf("最终骰子点数列表：\n");
	for (int dice : diceList)
		printf("%d ", (dice % 6) + 1);
	putchar('\n');
}

/*
*红桃Q:32,方片Q:31,红桃2:30,方片2:29,红桃8:28,方片8:27,红桃4:26,方片4:25,
*黑桃10:24,梅花10:23,黑桃4:22，梅花4:21,黑桃6:20,梅花6:19,黑桃J:18,梅花J:17,
*红桃10:16,方片10:15,红桃6:14,方片6:13,红桃7:12,方片7:11,黑桃9:10,梅花9:9，
*黑桃8:8,梅花8:7,黑桃7:6,梅花7:5,黑桃5:4,梅花5:3,红桃3:2,大王:1
*/
void DaXuanPrint(const std::string& finallySeed)
{
	std::vector<uint64_t> randomList = GenRandomListBySeed(finallySeed, 32);
	printf("随机序列：\n");
	for (uint64_t num : randomList)
		printf("%d ", (int)(num % 32));
	printf("\n\n");

	std::vector<int> cardList = Shuffle(randomList, 32);
	printf("洗牌后的序列：\n");
	for (int card : cardList)
		printf("%d ", card);
	printf("\n\n");

	static std::string cardNumStr[33] =
	{
			"",
			"大王",  "红桃3", "梅花5", "黑桃5", "梅花7", "黑桃7", "梅花8",  "黑桃8",
			"梅花9", "黑桃9", "方片7", "红桃7", "方片6", "红桃6", "方片10", "红桃10",
			"梅花J", "黑桃J", "梅花6", "黑桃6", "梅花4", "黑桃4", "梅花10", "黑桃10",
			"方片4", "红桃4", "方片8", "红桃8", "方片2", "红桃2", "方片Q",  "红桃Q"
	};

	printf("可视化牌序列：\n");
	for (auto card : cardList)
		printf("%s ", cardNumStr[card].c_str());
	putchar('\n');
}

int main()
{
	// 1，生成最终洗牌种子
	const std::string finallySeed = GenFinallySeed("o0fGqmei", "mgFqmN5z", "", "",
		"", "", "", "",
		"", "", "6511474087809777665");

	// 2，根据各种不同玩法认定不同参数
	// 2.1，BlackJack玩法，6副牌，最大牌面值13
	// PokerPrintShuffle(finallySeed, 312, 13);

	// 2.2，骰子玩法，使用3个骰子
	// DiceShuff(finallySeed, 3);

	// 2.2，百家乐玩法，6副牌，最大牌面值13
	// PokerPrintShuffle(finallySeed, 312, 13);

	// 2.3，打拤玩法，1副牌，最大牌面值9或13
	// PokerPrintShuffle(finallySeed, 52, 9);

	// 2.4，牛牛玩法，1副牌，最大牌面值13
	// PokerPrintShuffle(finallySeed, 52, 13);

	// 2.5，打旋玩法，对应比较特殊
	DaXuanPrint(finallySeed);

	getchar();
	return 0;
}