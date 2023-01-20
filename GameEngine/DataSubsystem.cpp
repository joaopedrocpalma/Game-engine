#include "DataSubsystem.h"

std::vector<std::string> DataSubsystem::GetElements(const std::string& tab, lua_State* L)
{
	/* Like GLSL, Lua allows us to execute functions by defining them
	as strings. The reason we're doing this is that it is easier to poll
	the keys from a Lua file using Lua syntax than it is using C++.

	The function below is called getElements. It accepts a string saying which
	global table it should be applied to (in this case). The pairs operator then
	iterates through the length of the table, checking the tables within it. For
	each of these tables, it appends their name, delineated with a '|' symbol. */

	std::string source =
		"function getElements(tab) "
		"s = \"\""
		"for k, v in pairs(_G[tab]) do "
		"    s = s..k..\"|\" "
		"    end "
		"return s "
		"end";

	/* We load the function using the loadstring function, then set up our
	default preamble. We then use getGlobal to access the getElements
	function, and pass in the name of the table we wish to explore (in this
	case, elementList, or 'tab'). The second lua_pcall executes the function
	we've loaded. */

	luaL_loadstring(L, source.c_str());
	lua_pcall(L, 0, 0, 0);
	lua_getglobal(L, "getElements");
	lua_pushstring(L, tab.c_str());
	lua_pcall(L, 1, 1, 0);

	/* The return from the function will be a single string, so we'll need to
	parse it.  This is why we added the separation character in the function
	code. We simply iterate through ans, populating a temp string, and push
	temp onto elements whenever the separation character is reached. */

	std::string ans = lua_tostring(L, -1);
	std::vector<std::string> elements;
	std::string temp = "";
	for (unsigned int i = 0; i < ans.size(); i++) {
		if (ans.at(i) != '|') {
			temp += ans.at(i);
		}
		else {
			elements.push_back(temp);
			temp = "";
		}
	}
	std::sort(elements.begin(), elements.end());

	/* We clean up after ourselves as best we can. */

	int n = lua_gettop(L);
	lua_pop(L, 1);

	/* Lastly, return the list of elements. With thanks to Elias Daler.*/

	return elements;
}

lua_State* DataSubsystem::GetLuaFile(const char* file_path)
{
	std::fstream check_file;
	check_file.open(file_path);
	if (check_file.fail()) {
		std::cout << "\n[Data error] File (" << file_path << ") not found!\nCheck directory path and typos\n";
	}
	else {
		// Load the lua libraries, read file data from a given file path, and return a lua file pointer.
		lua_State* lua_file;
		lua_file = luaL_newstate();
		luaL_dofile(lua_file, file_path); // E.g., "../Config/window.lua"
		luaL_openlibs(lua_file);
		lua_pcall(lua_file, 0, 0, 0);

		return lua_file;
	}
	check_file.close();
}

//std::string DataSubsystem::GetHTMLFile(std::string file_path)
//{
//	return std::string();
//}
