/*==============================================
         The Willow encryption algorithm
              By: Galinski Benjamin
================================================
==  Stable v1.0.0
==
==  This program can take a json file, encrypt
==    it with a key and turn it into a given
==    ascii picture using a template.
==  It can then take an ascii picture and a key,
==    and construct the original json file.
==
==  This program was made for nothing more than
==    pure fun, and started off as being just
==    intended to be used as a shitpost towards
==    the game of Shield Cat, made by
==    CyanSorcery.
==  Things got out of hand after some drinks,
==    and now we're here.
==  Go play the game, it's pretty fun.
==============================================*/

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdint>
#include <iomanip>

#include "mainConfig.hpp"
#include "nlohmann/json.hpp"
#include "manual.h"

//===============STRUCTS=======================

//struct for holding the command line arguments
struct inputInfo
{
	static uint8_t pathToFollow;
//	static uint16_t level;
	static char fill;
	static std::string fileTarget;
	static std::string graphicTarget;
	static std::string keyTarget;
	static std::string outTarget;
	
	static void dump()
	{
		std::cout << "pathToFollow: " << (int)inputInfo::pathToFollow << std::endl;
//		std::cout << "level: " << (int)inputInfo::level << std::endl;
		std::cout << "fill: " << inputInfo::fill << std::endl;
		std::cout << "fileTarget: " << inputInfo::fileTarget << std::endl;
		std::cout << "graphicTarget: " << inputInfo::graphicTarget << std::endl;
		std::cout << "keyTarget: " << inputInfo::keyTarget << std::endl;
		std::cout << "outTarget: " << inputInfo::outTarget << std::endl;
	}
};

uint8_t inputInfo::pathToFollow = 0;
//uint16_t inputInfo::level = 5;
char inputInfo::fill = '@';
std::string inputInfo::fileTarget = "";
std::string inputInfo::graphicTarget = "";
std::string inputInfo::keyTarget = "Breadfish";
std::string inputInfo::outTarget = "./out";


//struct for holding json content as a stream
struct jData
{
	static uint64_t count;
	static std::stringstream ss;
	
	static uint64_t get_countMod()
	{
		return jData::count*2;
	}
	
	static void build(std::string &jsonFile)
	{
		//Create flat json
		std::ifstream f_target(jsonFile, std::ios::in);
		nlohmann::json jData;
		f_target >> jData;
		f_target.close();
		jData = jData.flatten();
		
		//Put flat json data into stream and get count
		std::stringstream ss_jData_temp;
		char i;
		ss_jData_temp << jData;
		while(ss_jData_temp.get(i))
		{
			jData::count++;
			jData::ss << i;
		}
	}
	
};

uint64_t jData::count = 0;
std::stringstream jData::ss;


//struct for holding the ascii art as a stream
struct graphic
{
	static uint64_t count;
	static std::stringstream ss;
	
	static void build(std::string &graphicFile, char &fill)
	{
		std::ifstream f_graphic(graphicFile, std::ios::in);
		char i;
		while(f_graphic.get(i))
		{
			if(i == fill) graphic::count++;
			graphic::ss << i;
		}
	}
	
};

uint64_t graphic::count = 0;
std::stringstream graphic::ss;


//======================PROTOTYPES============================

bool encrypt(void);
bool decrypt(void);
bool count(void);
bool willowEncrypt(void);
bool varify(void);
bool monochrome(void);


//=====================FUNCTIONS==============================

//interprests user input and builds inputInfo
int main(int argc, char *argv[])
{
	std::string testVal;
	
	for(uint8_t i = 1; i < argc; i++)
	{
		testVal = argv[i];
		
		//============OPERATIONS====================
		if(testVal == "-e" || testVal == "--encryption")
		{
			inputInfo::pathToFollow = 1;
			inputInfo::fileTarget = argv[++i];
			inputInfo::graphicTarget = argv[++i];
			inputInfo::keyTarget = argv[++i];
		}
		else if(testVal == "-d" || testVal == "--decrypt")
		{
			inputInfo::pathToFollow = 2;
			inputInfo::fileTarget = argv[++i];
			inputInfo::keyTarget = argv[++i];
		}
		else if(testVal == "-c" || testVal == "--count")
		{
			inputInfo::pathToFollow = 3;
			std::string temp = argv[++i];
			
			if(temp.substr(temp.size() - 5) == ".json")
			{
				inputInfo::fileTarget = temp;
			}
			else
			{
				inputInfo::graphicTarget = temp;
			}
			
			if(i+1 < argc)
			{
				temp = argv[++i];
				if(temp.substr(temp.size() - 5) == ".json")
				{
					inputInfo::fileTarget = temp;
				}
				else
				{
					inputInfo::graphicTarget = temp;
				}
			}
			
		}
		else if(testVal == "-m" || testVal == "--monochrome")
		{
			inputInfo::pathToFollow = 4;
			inputInfo::graphicTarget = argv[++i];
			inputInfo::fileTarget = argv[++i];
		}
		//==============FLAGS=======================
		else if(testVal == "-f" || testVal == "--fill")
		{
			inputInfo::fill = argv[++i][0];
		}
		else if(testVal == "-o" || testVal == "--out")
		{
			inputInfo::outTarget = argv[++i];
		}
		//============OTHER=========================
		else if(testVal == "-h" || testVal == "--help")
		{
			print_man();
			return 1;
		}
		else if(testVal == "-t" || testVal == "--tellmemore")
		{
			tellThemMore();
			return 1;
		}
		else
		{
		youDunGoofed();
		return 1;
		}
	}
	
	//where to go?
	if(inputInfo::pathToFollow == 1)      //--encrypt
	{
		if(encrypt()) return 1;
	}
	else if(inputInfo::pathToFollow == 2) //--decrypt
	{
		if(decrypt()) return 1;
	}
	else if(inputInfo::pathToFollow == 3) //--count
	{
		if(count()) return 1;
	}
	else if(inputInfo::pathToFollow == 4) //--monochrome
	{
		if(monochrome()) return 1;
	}
	
	return 0;
}

//==============================================================

bool encrypt(void)
{
	
	jData::build(inputInfo::fileTarget);
	graphic::build(inputInfo::graphicTarget, inputInfo::fill);
	
	if(varify()) return 1;
	
	if(willowEncrypt()) return 1;
	
	return 0;
}

//=============================================

bool decrypt(void)
{
	std::ifstream f_data(inputInfo::fileTarget, std::ios::in);
	std::string temp = "";
	bool odd = false;
	uint64_t iter = 0;
	char i;
	
	char x;
	uint16_t brac_count = 0;
	
	while(f_data.get(i))
	{
		//if a hex number "0123456789" (48-57), "abcdef" (97-102)
		if(((int)i >= 48 && (int)i <= 57) || ((int)i >= 97 && (int)i <= 102))
		{
			temp += i;
			
			//appends 2 chars then translates them
			if(odd)
			{
				x = (char)((inputInfo::keyTarget[(iter++ % inputInfo::keyTarget.size())]) ^ (std::stoi(temp, nullptr, 16)));
				if(x == '{') brac_count++;
				else if(x == '}') brac_count--;
				
				//if the first bracket of the json has met its closing bracket (end of json data)
				if(brac_count == 0)
				{
					jData::ss << x;
					f_data.close();
					
					nlohmann::json jsonFile;
					jData::ss >> jsonFile;
					jsonFile = jsonFile.unflatten();
					
					std::ofstream f_out(inputInfo::outTarget, std::ios::out);
					f_out << jsonFile.dump();
					f_out.close();
					return 0;
				}
				
				jData::ss << x;
				temp.clear();
			}
			
			odd = !odd;
		}
	}
	
	f_data.close();
	return 0;
}
	
//==============================================================

bool monochrome(void)
{
	std::ifstream f_graphicOld(inputInfo::fileTarget, std::ios::in);
	std::ofstream f_graphic(inputInfo::outTarget, std::ios::out);
	
	char i;
	while(f_graphicOld.get(i))
	{
		//if the char you want to NOT change
		if(i == inputInfo::graphicTarget[0] || i == '\n') f_graphic << i;
		//else replace with your fill char
		else f_graphic << inputInfo::fill;
	}
	
	f_graphic.close();
	f_graphicOld.close();
	return 0;
}

//================================================================

bool count(void)
{
	if((inputInfo::fileTarget != "") && (inputInfo::graphicTarget != ""))
	{
		jData::build(inputInfo::fileTarget);
		graphic::build(inputInfo::graphicTarget, inputInfo::fill);
		if(varify()) return 1;
		std::cout << "json data count is: " << jData::get_countMod() << std::endl;
		std::cout << "Template has: " << graphic::count << " " << inputInfo::fill <<"'s"  << std::endl;
		std::cout << "You're good to go!" << std::endl;
	}
	else if(inputInfo::fileTarget != "")
	{
		jData::build(inputInfo::fileTarget);
		std::cout << "json data count is: " << jData::get_countMod() << std::endl;
		return 0;
	}
	
	else if(inputInfo::graphicTarget != "")
	{
		graphic::build(inputInfo::graphicTarget, inputInfo::fill);
		std::cout << "Template has: " << graphic::count << " " << inputInfo::fill  << "'s" << std::endl;
		return 0;
	}
	
	return 0;
}

//==============================================================

bool willowEncrypt(void)
{
	std::ofstream f_out(inputInfo::outTarget, std::ios::out);
	std::stringstream out_temp;
	char charData;
	char charGraphic;
	char temp;
	uint64_t iter = 0;
	uint64_t jDataCount = jData::count;
	
	if(!f_out.is_open()) return 1;
	
	//for every char in the flat json
	while(jData::ss.get(charData))
	{
		//XOR the first char of the key with the first char of json, second with second...
		temp = inputInfo::keyTarget[(iter++ % inputInfo::keyTarget.size())];
		out_temp << std::setfill('0') << std::setw(2) << std::hex << (int)(charData^temp);
	}
	
	//until the encrypted stream is the same size as the number of fill chars in the ascii art
	while((jDataCount+2) < graphic::count)
	{
		//fill empty space with random nonsense
		temp = inputInfo::keyTarget[(iter++ % inputInfo::keyTarget.size())];
		out_temp << std::setfill('0') << std::setw(2) << std::hex << (((uint8_t)std::rand())^temp);
		jDataCount += 2;
	}
	
	//if the number of fill chars in the art is odd, it will need the one extra random nonsense
	while(jDataCount < graphic::count)
	{
		out_temp << std::hex << (((uint8_t)std::rand())%16);
		jDataCount++;
	}
	
	//begin to map the encrypted data to the ascii art
	while(graphic::ss.get(charGraphic))
	{
		if(charGraphic == inputInfo::fill)
		{
			out_temp.get(charData);
			f_out << charData;
		}
		else
		{
			f_out << charGraphic;
		}
	}
	
	f_out.close();
	return 0;
}

//===========================================
	
bool varify(void)
{
	long long int diff = (jData::get_countMod() - graphic::count);
	if(diff > 0)
	{
		std::cout << "ERROR!" << std::endl;
		std::cout << "The ascii template has " << graphic::count << " " << inputInfo::fill << "'s" << std::endl;
		std::cout << "The json file is " << jData::get_countMod() << " long (char length of the flattened json contents times 2)" << std::endl;
		std::cout << "Your ascii template is " << diff << " characters too small" << std::endl;
		std::cout << "You can use '-c' to check the sizes of these files" << std::endl;
		return 1;
	}
	
	return 0;
}
