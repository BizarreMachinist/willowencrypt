#ifndef MANUAL_H
#define MANUAL_H

//  Stable v1.0.0

void print_man()
{
	std::string manual[] =
		{
		"===============================================",
		"Welcome to the Willow encryption algorithm!",
		"Want to take a boring old json file and turn it into a lovely ascii picture that's cuss near impossible to read?",
		"Want to then extract an entire json from that image?",
		"Well then mate, this thing is for you!",
		"",
		"DISCLAIMER: Don't actually trust the strength of this encryption. I'm not a security expert. I'm not a pentester.",
		"This program was made for a one off joke, and was never intented to be used for serious applications.",
		"I take no responsibility for files getting cracked, or files failing to decrypt into their exact original states.",
		"And certainly don't forget the key you used to encrypt. Unless you find a flaw in the encryption process, I haven't written a way to get that data back.",
		"I completely refuse to add a backdoor of ANY kind (period).",
		"But certainly, certainly above all else, HAVE FUN!",
		"",
		"Typical use cases:",
		"  willowencrypt [Flags]* (-e || --encrypt) <json to encrypt> <ascii template> <key>",
		"  willowencrypt [Flags]* (-d || --decrypt) <lvbn file> <key>",
		"  willowencrypt [Flags]* (-c || --count) (<ascii template> || <json file>) (<ascii template> || <json file>)*",
		"  willowencrypt [Flags]* (-m || --monochrome) <char to not change> <ascii art>",
		"    *Optional",
		"",
		"Operations:",
		"  (-e || --encrypt) <args>    Create lvbn from json. See 'Typical use cases'",
		"  (-d || --decrypt) <args>    Create json from lvbn. See 'Typical use cases'",
		"  (-c || --count) <args>      Counts how many fill chars are in the image template",
		"                                and/or minimum fill needed for a json.",
		"                                Requires file extension for json to be '.json'",
		"  (-m || --monochrome)        If an ascii image is generated from an actual image,",
		"                                this can change all chars, but 1 into another char.",
		"                                Creating a 'monochrome' image that's suitable for",
		"                                this encryption",
		"Flags:",
		"  (-o || --out) <out file>    Set the location and name of output file.",
		"  (-f || --fill) <char>       Set which character to count/replace.",
		"                                Defaults to '@'",
		"  (-s || --static) <char>     Set which char to replace the 'char to not change' with.",
		"                                Often used to set the background of an image to '.'s",
//		"  (-l || --level) <int>       Set the number to iterations of masking",
//		"                                Defaults to 5. Even values, have a chance to not",
//		"                                be secure. See '-m' for more",
		"Other:",
		"  (-h || --help)              Don't bother, you're already here",
		"  (-m || --tellmemore!)       But wait, THERE'S MORE!",
		"",
		"If something contains a space anywhere in it, qoutations must be used, but it's safer to use them regardless",
		"==============================================="
		};
	
	for(auto line : manual) std::cout << line << std::endl;
}

void tellThemMore()
{
	std::string more[] =
		{
		"===============================================",
		"This program was made for advanced shitposting reasons.",
		"The target?",
		"A game called Shield Cat, made by CyanSorcery.",
		"She was going on about maybe compressing/encrypting the save files just",
		"  enough so hacking the game wasn't as simple as just modifying an ascii file.",
		"It was originally a simpler program that took a save file from a very specific version of the game,",
		"  and turn it into just one type of ascii image, a picture of Willow from the game.",
		"Henceforth, Willow encryption.",
		"",
		"After some drunk programming I ended up here.",
		"",
		"The actual encryption process is quite simple.",
		"XOR the first char of your json with the first char of the key,",
		"then XOR the second with the second, and so on,",
		"looping back to the begining of the key if it runs out of chars in the key.",
//		"It does this process an odd number times for the whole json file (this case 3),",
		"With more work it would be able to do this process X number of times,",
		"  but doing it an even number of times has the possibility of just",
		"  decrypting what was just encrypted, and writing that to the ascii image.",
		"All encrypted chars are then read as hex, but taken as literal chars",
		"(value 69 is now chars '6' & '9').",
		"If your json is too short for a given ascii image,",
		"It'll fill any missing space with pseudorandom data.",
		"Json starts and ends with {}, we just read until the first { gets its matching }.",
		"We know that anything after that is literally garbage.",
		"==============================================="
		};
	
	for(auto line : more) std::cout << line << std::endl;
}

void youDunGoofed()
{
	std::string failed[] =
		{
		"===============================================",
		"Something went wrong",
		"Maybe try -h or --help",
		"==============================================="
		};
	
	for(auto line : failed) std::cout << line << std::endl;
}

#endif
