﻿#include<iostream>
#include<fstream>
#include<filesystem>
#include<map>
#include"User.h"
#include"Student.h"
#include"Docs.h"
#include"Server.h"
#include "ThirdPartyLib/colourStream.h"
#include"interactiveReader.h"

using namespace kerbal::utility::costream;
class Quit
{
};


//brif

template<std::ostream & os = std::cout, std::istream & is = std::cin>
void oneLineBrifOnStudent(const Server& server, const Student::LogicID& id)
{
	auto& s = server.getStudentByLogicId(id);
	costream<os>(GREY) << "姓名:\t" << s.getName() << ",\t" << "学号:\t" << s.getID() << std::endl;
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
void brifOnStudent(const Server& server, const Student::LogicID& id)
{
	auto& s = server.getStudentByLogicId(id);
	auto CSR = server.getCourseSelectionRecordIdByStudentId(id);
	auto className = server.getClassNameByClassID(s.getClass());
	costream<os>(GREY) << "姓名:\t" << s.getName() << std::endl;
	costream<os>(GREY) << "学号:\t" << s.getID() << std::endl;
	costream<os>(GREY) << "班级:\t" << className << std::endl;
	costream<os>(GREY) << "性别:\t" << s.getGender().to_string() << std::endl;;
	costream<os>(GREY) << "入学年份:\t" << s.getStartYear() << std::endl;
	costream<os>(GREY) << "成绩:\n" << std::endl;
	CourseSelectionRecord::GradeOfCourse sumGrade = 0;
	Course::ClassHourOfCourse sumClassHour = 0;
	for (auto i : server.getCourseSelectionRecordIdByStudentId(id))
	{
		const auto& csr = server.getCourseSelectionRecordByID(i);//csr for CourseSelectionRecord
		const auto& course = server.getCourseByCourseId(csr.getCourseID());
		sumGrade += csr.getGrade() * course.getClassHour();
		sumClassHour += course.getClassHour();
		if (csr.getGrade() >= 60.0)
			costream<os>(GREY) << "\t" << course.getName() << " : \t" << csr.getGrade() << std::endl;
		else
			costream<os>(RED) << "\t" << course.getName() << " : \t" << csr.getGrade() << std::endl;

	}
	if (sumClassHour > 0.5)
		costream<os>(GREY) << "\t平均成绩:" << sumGrade / sumClassHour << std::endl;

}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
void brifOfClass(const Server& server, const Student::StudentClassLogicalID& id)
{
	auto& className = server.getClassNameByClassID(id);
	auto students = server.getStudentLogicIdByClass(id);
	costream<os>(LIGHT_BLUE) << "班级:\t" << className << std::endl;
	for (auto s : students)
	{
		oneLineBrifOnStudent(server, s, os);
	}
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
void oneLineBrifOfCourse(const Server& server, const Course::CourseID& id)
{
	const auto& course = server.getCourseByCourseId(id);
	costream<os>(YELLOW) << "课程名:\t" << course.getName() << ",\t" << "课时:\t" << course.getClassHour() << std::endl;
}

//select

template<std::ostream & os = std::cout, std::istream & is = std::cin>
Student::StudentClassLogicalID selectClass(const Server& server)
{
	while (true)try
	{
		auto m = iReader::InteractiveReader<std::string>().read(is, os, "选择班级的方法", iReader::WithIn<std::string>({ "List","Name","Quit" }), iReader::StdIstreamStringReader());
		switch (m[0])
		{
		case 'N':
		{
			auto s = iReader::InteractiveReader<Student::StudentClassName>().read(is, os, "班级的名字", iReader::NoRestrict<Student::StudentClassName>(), iReader::StdIstreamStringReader());
			return server.getClassLogicalIdByClassName(s);
		}
		case 'L':
		{
			auto pair = server.getClassesList();
			for (auto i = pair.first; i != pair.second; i++)
			{
				costream<os>(LIGHT_BLUE) << i->first << " " << i->second << std::endl;
			}
			break;
		}
		case 'Q':
			//[[fallthrough]]
		default:
			throw Quit();
			break;
		}
	}
	catch (CmdResalt & res)
	{
		costream<os>(LIGHT_RED) << res.operator const std::string & () << std::endl;
	}
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
Server::StudentIdSet selectStudent(const Server& server)
{
	while (true)
	{
		auto s = iReader::InteractiveReader<std::string>().read(is, os, "选择学生的条件", iReader::WithIn<std::string>({ "ID","Name","Class","Quit" }), iReader::StdIstreamStringReader());
		try
		{
			switch (s[0])
			{
			case 'I':
				return Server::StudentIdSet({ server.getStudentLogicIdByID(iReader::InteractiveReader<Student::ID>().read(is,os,"学生的ID",iReader::NoRestrict<Student::ID>(),iReader::StdIstreamStringReader())) });
				break;
			case 'N':
				return server.getStudentLogicIdByName(iReader::InteractiveReader<Student::UserName>().read(is, os, "学生的姓名", iReader::NoRestrict<Student::UserName>(), iReader::StdIstreamStringReader()));
				break;
			case 'C':
				return server.getStudentLogicIdByClass(selectClass(server));
				break;
			case 'Q':
				//[[fallthrough]]
			default:
				throw Quit();
				break;
			}
		}
		catch (CmdResalt & res)
		{
			costream<os>(LIGHT_RED) << res.operator const std::string & () << std::endl;
		}
	}
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
Course::CourseID selectCourse(const Server& server)
{
	while (true)
	{
		auto s = iReader::InteractiveReader<std::string>().read(is, os, "选择课程的条件", iReader::WithIn<std::string>({ "Name","List","Quit" }), iReader::StdIstreamStringReader());
		try
		{
			switch (s[0])
			{
			case 'N':
			{
				auto name = iReader::InteractiveReader<std::string>().read(is, os, "课程的名字", iReader::NoRestrict<std::string>(), iReader::StdIstreamStringReader());
				return server.getCourseIdByCourseName(name);
			}
			case 'L':
			{
				const auto& iter = server.getCoursesRecord();
				for (auto i = iter.first; i != iter.second; i++)
				{
					oneLineBrifOfCourse<os, is>(server, i->first);
				}
			}
			case 'Q':
				//[[fallthrough]]
			default:
				throw Quit();
				break;
			}

		}
		catch (CmdResalt & res)
		{
			costream<os>(LIGHT_RED) << res.operator const std::string & () << std::endl;
		}

	}
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
Server::CourseSelectionRecordIdSet selectCSR(const Server& server)
{
	while (true)
	{
		auto s = iReader::InteractiveReader<std::string>(is, os, "选择选课记录的条件", iReader::WithIn<std::string>({ "Both","Student","Quit" }), iReader::StdIstreamStringReader());
		try
		{
			switch (s[0])
			{
			case 'S':
				return server.getCourseSelectionRecordIdByStudentId(selectStudent(server));
				break;
			case 'B':
				return Server::CourseSelectionRecordIdSet(
					{
					server.getCourseSelectionRecordIdByStudentIdAndCourseID(selectStudent(server),selectCourse(server))
					});
			case 'Q':
				//[[fallthrough]]
			default:
				throw Quit();
				break;
			}

		}
		catch (CmdResalt & res)
		{
			costream<os>(LIGHT_RED) << res.operator const std::string & () << std::endl;
		}
	}
}

//input
template<std::ostream & os = std::cout, std::istream & is = std::cin>
User inputUser(void)
{
	auto name = iReader::InteractiveReader<std::string>().read(is, os, "姓名", iReader::NoRestrict<std::string>(), iReader::StdIstreamStringReader());
	auto id = iReader::InteractiveReader<std::string>().read(is, os, "ID", iReader::NoRestrict<std::string>(), iReader::StdIstreamStringReader());
	auto gender = iReader::InteractiveReader<std::string>().read(is, os, "性别", iReader::WithIn<std::string>({ "Male","Female","Unknown" }), iReader::StdIstreamStringReader());
	//auto ID= iReader::
	return User(id, name, Gender(gender));
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
void addAdmin(Server& server)
{
	User user = inputUser<os, is>();
	auto pwd = iReader::InteractiveReader<User::PWD>().read
	(
		is, os,
		"管理员密码",
		iReader::NoRestrict<User::PWD>(),
		iReader::StdIstreamReader<User::PWD>()
	);
	user.setPWD(pwd);
	server.addUser(user);
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
void addStudent(Server& server)
{
	auto user = inputUser<os, is>();
	auto theclass = selectClass<os, is>(server);
	server.addStudent
	(
		Student
		(
			user,
			theclass,
			iReader::InteractiveReader<Student::StudentGrade>().read(is, os, "入学年份", iReader::NoRestrict<Student::StudentGrade>(), iReader::StdIstreamReader<Student::StudentGrade>())
		)
	);
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
void addClass(Server& server)
{
	server.addClass
	(
		iReader::InteractiveReader<Student::StudentClassName>().read
		(
			is,os,
			"班级名称",
			iReader::NoRestrict<Student::StudentClassName>(),
			iReader::StdIstreamReader<Student::StudentClassName>()
		)
	);
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
void addCourse(Server& server)
{
	auto courseName = iReader::InteractiveReader<Course::CourseName>().read
	(
		is, os,
		"课程名字",
		iReader::NoRestrict<Course::CourseName>(),
		iReader::StdIstreamReader<Course::CourseName>()
	);
	auto classHour = iReader<Course::ClassHourOfCourse>().read
	(
		is, os,
		"课时",
		iReader::InRange<Course::ClassHourOfCourse>(0.4, 8.0),
		iReader::StdIstreamReader<Course::ClassHourOfCourse>()
	);
	server.addCourse(Course(courseName, classHour));
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
int asStudent(const Server& server)
{
	try
	{
		auto id = iReader::InteractiveReader<Student::LogicID>().read(is, os, "ID", iReader::NoRestrict<Student::LogicID>(), iReader::StdIstreamReader<Student::LogicID>());
		auto pwd = iReader::InteractiveReader<Student::PWD>().read(is, os, "密码", iReader::NoRestrict<Student::PWD>(), iReader::StdIstreamReader<Student::PWD>());
		if (server.loginAsStudent(id, pwd))
		{
			brifOnStudent<os, is>(server, id);
		}
	}
	catch (const CmdResalt & res)
	{
		costream<os>(LIGHT_RED) << res.operator const std::string & () << std::endl;

	}
	catch (const Quit&)
	{
		return 0;
	}
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
void addCSR(Server& server)
{
	auto stuid = selectStudent<os, is>(server);
	auto course = selectCourse<os, is>(server);
	server.addCourseSelectionRecord(stuid, course);
}

template<std::ostream & os = std::cout, std::istream & is = std::cin>
int asAdmin(Server& server)
{
	return 2;
}
int __main__(void)
{
	std::filesystem::path serverPath("./data.json");
	std::filesystem::file_status serverFileStatus = std::filesystem::status(serverPath);

	Server myServer;
	if (std::filesystem::exists(serverFileStatus))
	{
		std::fstream fs(serverPath);
		std::istreambuf_iterator<char> begin(fs);
		std::istreambuf_iterator<char> end;
		std::string bufer(begin, end);
		json js(bufer);
		myServer = Server(js);
	}
	auto s = iReader::InteractiveReader<std::string>().read(std::cin, std::cout, "登陆名", iReader::WithIn<std::string>({ "s","student","a","admin" }), iReader::StdIstreamStringReader());
	switch (s[0])
	{
	case 's':
		return asStudent(myServer);
		break;
	case 'a':
		return asAdmin(myServer);
	default:
		break;
	}

	return 0;
}
int test(void)
{
	Server myServer;
	std::cout << "start" << std::endl;
	myServer.addClass("2b");
	myServer.addStudent(Student(User("123", "hh"), 0, 2019));
	myServer.addCourse(Course("lm", 1.0));
	myServer.addCourseSelectionRecord(*(myServer.getStudentLogicIdByName("hh").begin()), myServer.getCourseIdByCourseName("lm"));
	addStudent(myServer);
	selectCourse(myServer);
	for (auto s : selectStudent(myServer))
		brifOnStudent(myServer, s);
	auto s = myServer.getStudentLogicIdByClass(
		myServer.getClassLogicalIdByClassName("2b")
	);


	costream<std::cout>(LIGHT_RED) << Server(myServer.serialize()).serialize().dump(4) << std::endl;
	std::cout << myServer.serialize().dump(4) << std::endl;
	return 0;
}
int main(void)
{
	return 	__main__();

}