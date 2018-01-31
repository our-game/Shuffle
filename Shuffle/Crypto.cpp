#include "Crypto.h"
#include "botan/botan.h"

using namespace Botan;

namespace BotanCrypto{

	static string strValue = "";
	void init(){
		Botan::LibraryInitializer init;
	}

	string hexEncode(string& source){
		try{
			Botan::Pipe pipe(new Botan::Hex_Encoder);
			pipe.process_msg(source);
			SecureVector<byte> buffer = pipe.read_all();
			string str;
			str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			return str;
		}catch(...){
			return "";
		}
	}

	string hexDecode(string& source){
		try{
			Botan::Pipe pipe(new Botan::Hex_Decoder);
			pipe.process_msg(source);
			SecureVector<byte> buffer = pipe.read_all();
			string str;
			str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			return str;
		}catch(...){
			return "";
		}
	}
	
	string base64Encode(string& source){
		try{
			Botan::Pipe pipe(new Botan::Base64_Encoder);
			pipe.process_msg(source);
			SecureVector<byte> buffer = pipe.read_all();
			string str;
			str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			return str;
		}catch(...){
			return "";
		}
	}

	string base64Decode(string& source){
		try{
			Botan::Pipe pipe(new Botan::Base64_Decoder);
			pipe.process_msg(source);
			SecureVector<byte> buffer = pipe.read_all();
			string str;
			str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			return str;
		}catch(...){
			return "";
		}
	}

	string md5(string& source)
	{
		try
		{
			Botan::Pipe pipe(new Botan::Hash_Filter("MD5"), new Hex_Encoder);
			pipe.process_msg(source);
			SecureVector<byte> buffer = pipe.read_all();
			string str;
			str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			return str;
		 }
		catch(...)
		{	
			return "";
		}
	}

	string sha1(string& source){
		try{
			 Botan::Pipe pipe(new Botan::Hash_Filter("SHA-1"), new Hex_Encoder);
			 pipe.process_msg(source);
			 SecureVector<byte> buffer = pipe.read_all();
			 string str;
			 str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			 return str;
		}catch(...){
			return "";
		}
	}

	string hmacsha1(string& key, string& source){
		try{
			string key1 = hexEncode(key);
			SymmetricKey mac_key(key1);
			Pipe pipe(new Chain(new MAC_Filter("HMAC(SHA-1)",mac_key), new Hex_Encoder));
			pipe.process_msg(source);
			SecureVector<byte> buffer = pipe.read_all();
			string str;
			str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			return str;
		}catch(...){
			return "";
		}
	}

	string hmacmd5(string& key, string& source){
		try{
			string key1 = hexEncode(key);
			SymmetricKey mac_key(key1);
			Pipe pipe(new Chain(new MAC_Filter("HMAC(MD5)",mac_key), new Hex_Encoder));
			pipe.process_msg(source);
			SecureVector<byte> buffer = pipe.read_all();
			string str;
			str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			return str;
		}catch(...){
			return "";
		}
	}

	string hmacsha1base64(string& key, string& source){
		try{
			string key1 = hexEncode(key);
			SymmetricKey mac_key(key1);
			Pipe pipe(new Chain(new MAC_Filter("HMAC(SHA-1)",mac_key), new Base64_Encoder));
			pipe.process_msg(source);
			SecureVector<byte> buffer = pipe.read_all();
			string str;
			str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			return str;
		}catch(...){
			return "";
		}
	}

	string crc32Check(string& data){
		try{
			Pipe pipe(new Hash_Filter("CRC32"), new Hex_Encoder);
			pipe.process_msg(data);
			SecureVector<byte> buffer = pipe.read_all();
			string str;
			str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			return str;
		}catch(...){
			return "";
		}
	}

	string tripleDESDecode(string& key, string& source){
		try{
			const BlockCipher* cipher_proto = global_state().algorithm_factory().prototype_block_cipher("TripleDES");
			const u32bit key_len = cipher_proto->maximum_keylength();
			const u32bit iv_len = cipher_proto->block_size();
			key = key.substr(0, key_len);
			string keyhex = hexEncode(key);
			SymmetricKey mac_key(keyhex);
			string ivkey = key.substr(0, iv_len);
			string ivkeypas = hexEncode(ivkey);
			InitializationVector iv(ivkeypas);
			Pipe pipe(get_cipher("TripleDES/CBC", mac_key, iv, DECRYPTION));
			pipe.process_msg(source);
			//return pipe.read_all_as_string(0);
			SecureVector<byte> buffer = pipe.read_all();
			string str;
			str.append(reinterpret_cast<const char*>(buffer.begin()), buffer.size());
			return str;
		}catch(...){
			return "";
		}
	}
}