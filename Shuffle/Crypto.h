#include <string>
using namespace std;

namespace BotanCrypto{
	extern __declspec(dllexport) void init();
	extern __declspec(dllexport) string hexEncode(string& source);
	extern __declspec(dllexport) string hexDecode(string& source);
	extern __declspec(dllexport) string base64Encode(string& source);
	extern __declspec(dllexport) string base64Decode(string& source);
	extern __declspec(dllexport) string md5(string& source);
	extern __declspec(dllexport) string sha1(string& source);
	extern __declspec(dllexport) string hmacsha1(string& key, string& source);
	extern __declspec(dllexport) string hmacmd5(string& key, string& source);
	extern __declspec(dllexport) string hmacsha1base64(string& key, string& source);
	extern __declspec(dllexport) string crc32Check(string& data);
	extern __declspec(dllexport) string tripleDESDecode(string& key, string& source);

}