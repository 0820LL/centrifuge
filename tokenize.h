/*
 * Copyright 2011, Ben Langmead <langmea@cs.jhu.edu>
 *
 * This file is part of Bowtie 2.
 *
 * Bowtie 2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Bowtie 2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Bowtie 2.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TOKENIZE_H_
#define TOKENIZE_H_

#include <string>
#include <sstream>
#include <limits>

using namespace std;

/**
 * Split string s according to given delimiters.  Mostly borrowed
 * from C++ Programming HOWTO 7.3.
 *
 *
 */
template<typename T>  //T代表一种类型
static inline void tokenize(     //內联函数
	const string& s,     //引用作为参数  const 说明不能通过引用s修改引用s指向的对象的值。
	const string& delims,
	T& ss,
	size_t max = std::numeric_limits<size_t>::max())    //returns the largest finite value of the given type(size_t)
{
	//string::size_type lastPos = s.find_first_not_of(delims, 0);
	string::size_type lastPos = 0;    // size_type是size_t类型  lastPos用来指开始搜索的位置
	string::size_type pos = s.find_first_of(delims, lastPos);    //return the position of the first character that matches.
	while (string::npos != pos || string::npos != lastPos) {    //npos = -1  如果搜索的到
		ss.push_back(s.substr(lastPos, pos - lastPos));  //返回子字符串 参数是起始位置和长度。
		lastPos = s.find_first_not_of(delims, pos);  //返回第一个不匹配字符的位置
		pos = s.find_first_of(delims, lastPos);
		if(ss.size() == (max - 1)) {  //size()返回字符串长度
			pos = string::npos;
		}
	}
}

/*
*
*/
template<typename T>
static inline void tokenize(const std::string& s, char delim, T& ss) {
	std::string token;  //  token是个空字符串。 
	std::istringstream iss(s);    //构造istringstream对象iss
	while(getline(iss, token, delim)) {  //从iss中取characters放入token中，直到发现字符delim为止。
		ss.push_back(token);
	}
}

#endif /*TOKENIZE_H_*/
