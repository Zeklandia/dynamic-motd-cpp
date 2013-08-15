#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <cstdlib>

#include <time.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>

#include <fstream>

#include <unistd.h>
#include <sys/utsname.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <sys/sysinfo.h>
#include <linux/sysinfo.h>
#include <linux/kernel.h>

#include <utmp.h>

#include <ncurses.h>

using namespace std;

int main()
{
	//Begin loading information
	std::cout << "Loading..." << endl;
	system("reset");

	//Set colors
	//     Color				ASCII Code
	string color_default		("\e[0;0m");
	string red					("\e[0;31m");
	string red_bold				("\e[1;31m");
	string red_light			("\e[2;31m");
	string red_italic			("\e[3;31m");
	string red_underlined		("\e[4;31m");
	string green				("\e[0;32m");
	string green_bold			("\e[1;32m");
	string green_light			("\e[2;32m");
	string green_italic			("\e[3;32m");
	string green_underlined		("\e[4;32m");
	string yellow				("\e[0;33m");
	string yellow_bold			("\e[1;33m");
	string yellow_light			("\e[2;33m");
	string yellow_italic		("\e[3;33m");
	string yellow_underlined	("\e[4;33m");
	string blue					("\e[0;34m");
	string blue_bold			("\e[1;34m");
	string blue_light			("\e[2;34m");
	string blue_italic			("\e[3;34m");
	string blue_underlined		("\e[4;34m");
	string magenta				("\e[0;35m");
	string magenta_bold			("\e[1;35m");
	string magenta_light		("\e[2;35m");
	string magenta_italic		("\e[3;35m");
	string magenta_underlined	("\e[4;35m");
	string cyan					("\e[0;36m");
	string cyan_bold			("\e[1;36m");
	string cyan_light			("\e[2;36m");
	string cyan_italic			("\e[3;36m");
	string cyan_underlined		("\e[4;36m");
	string gray					("\e[0;37m");
	string gray_bold			("\e[1;37m");
	string gray_light			("\e[2;37m");
	string gray_italic			("\e[3;37m");
	string gray_underlined		("\e[4;37m");
	string white				("\e[0;97m");
	string white_bold			("\e[1;97m");
	string white_light			("\e[2;97m");
	string white_italic			("\e[3;97m");
	string white_underlined		("\e[4;97m");

	//System stats
	struct utsname uname_info;
	uname(&uname_info);
	const long minute = 60;
	const long hour = minute * 60;
	const long day = hour * 24;
	const double megabyte = 1024 * 1024;
	struct sysinfo uname_system_info;
	sysinfo (&uname_system_info);

	//Get time
	time_t hex_time;
	time (&hex_time);
	string datetime = ctime(&hex_time);
	datetime.erase(std::remove(datetime.begin(), datetime.end(), '\n'), datetime.end());

	//Get hostname
	char hostname[128];
	gethostname(hostname, sizeof hostname);

	//Get WLAN IP address
	string wlan_ip;
	int wlan_ip_address;
	struct ifreq wlan_ip_address_numeric;
	wlan_ip_address = socket(AF_INET, SOCK_DGRAM, 0);
	wlan_ip_address_numeric.ifr_addr.sa_family = AF_INET;
	strncpy(wlan_ip_address_numeric.ifr_name, "wlan0", IFNAMSIZ-1);
	ioctl(wlan_ip_address, SIOCGIFADDR, &wlan_ip_address_numeric);
	close(wlan_ip_address);
	wlan_ip = inet_ntoa(((struct sockaddr_in *)&wlan_ip_address_numeric.ifr_addr)->sin_addr);

	//Get LAN IP address
	string lan_ip;
	int lan_ip_address;
	struct ifreq lan_ip_address_numeric;
	lan_ip_address = socket(AF_INET, SOCK_DGRAM, 0);
	lan_ip_address_numeric.ifr_addr.sa_family = AF_INET;
	strncpy(lan_ip_address_numeric.ifr_name, "eth0", IFNAMSIZ-1);
	ioctl(lan_ip_address, SIOCGIFADDR, &lan_ip_address_numeric);
	close(lan_ip_address);
	lan_ip = inet_ntoa(((struct sockaddr_in *)&lan_ip_address_numeric.ifr_addr)->sin_addr);

	//Get kernel version
	string kernel_version = uname_info.release;

	//Get RAM size in kB
	//MEMSIZE=`cat /proc/meminfo | grep MemTotal | awk {'print $2'}`
	//printf ("total RAM   : %5.1f MB" << endl <<, si.totalram / megabyte);
	string ram_size = "RAM";

	//Get current users, jobs, login times, and locations
	string user_stats;
	user_stats = system("w | awk 'NR==1' | cut -c2-");

	//Get username
	string username = getenv("USER");

	//Get time, location, length, and other details for last login
	//LASTLOGIN=`last -n 2 -R $USER | awk 'NR==2'`
	string last_login;
	last_login = system("last -n 2 -R $USER | awk 'NR==2'");

	//Get home directory path
	string home_path = getenv("HOME");

	//Get the current number of this user's active processes
	//PROCOUNT=`ps -Afl | wc -l`
	//printf ("process count : %d" << endl <<, si.procs);
	string process_count;
	process_count = (uname_system_info.procs);

	//Get this user's limit on processes
	//PROLIMIT=`ulimit -u`
	string process_limit;
	process_limit = system("cat /proc/meminfo | grep MemTotal | awk {'print $2'}");

	//Print the location and ZIP code being used for weather
	//WLOC=`weather $ZIP | grep 'Current conditions at' | awk '{print $4}'`
	string weather_location = "location";
	string weather_zip = "zip";

	//Get the temperature
	//WTEMP=`weather $ZIP | grep 'Temperature:' | awk '{print $2}'`
	string weather_temperature = "Temperature";

	//Get the weather conditions (if there are any)
	//WCOND=`weather $ZIP | grep 'Weather:' | cut -d: -f2 | cut -c2-`
	string weather_conditions = "Weather conditions";

	//Get the sky conditions
	//WSKY=`weather $ZIP | grep 'Sky conditions:' | cut -d: -f2 | cut -c2-`
	string weather_sky_conditions = "Sky conditions";

	//Custom section
	string custom_header = "Custom Command Stats";

	string custom_title = "Custom Command";

	string custom_command;
	custom_command = system("echo Custom Command");

	string custom_command_output = custom_command;

	//Finished!
	std::cout << "Done!" << endl;
	system("reset");

	/*
	 * Old output
	 *  cout << cyan << ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=[ " << red_bold << "System Stats" << cyan << " ]=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:" << endl
	 *  		<< cyan << ":   " << white_bold << "Date/Time" << cyan << " = " << green_bold << datetime << endl
	 *  		<< cyan << ":    " << white_bold << "Hostname" << cyan << " = " << green_bold << hostname << endl
	 *  		<< cyan << ":     " << white_bold << "WLAN IP" << cyan << " = " << green_bold << wlan_ip << endl
	 *  		<< cyan << ":      " << white_bold << "LAN IP" << cyan << " = " << green_bold << lan_ip << endl
	 *  		<< cyan << ":      " << white_bold << "Kernel" << cyan << " = " << green_bold << kernel_version << endl
	 *  		<< cyan << ":      " << white_bold << "Memory" << cyan << " = " << green_bold << ram_size << " mB" << endl
	 *  		<< cyan << ":       " << white_bold << "Stats" << cyan << " = " << green_bold << user_stats << endl;
	 *
	 *  cout << cyan << ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:[ " << red_bold << "User Stats" << cyan << " ]:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:" << endl
	 *  		<< cyan << ":    " << white_bold << "Username" << cyan << " = " << green_bold << username << endl
	 *  		<< cyan << ":  " << white_bold << "Last Login" << cyan << " = " << green_bold << last_login << endl
	 *  		<< cyan << ":	" << white_bold << "Home" << cyan << " = " << green_bold << home_path << endl
	 *  		<< cyan << ":   " << white_bold << "Processes" << cyan << " = " << green_bold << process_count << " of " << process_limit << endl;
	 * 
	 *  cout << cyan << ":=:=:=:=:=:=:=:=:=:=:=:=:=:[ " << red_bold << "Internet Weather Stats" << cyan << " ]:=:=:=:=:=:=:=:=:=:=:=:=:=:" << endl
	 *  		<< cyan << ":    " << white_bold << "Location" << cyan << " = " << green_bold << weather_location << ", " << weather_zip << endl
	 *  		<< cyan << ":	   " << white_bold << "Temp" << cyan << " = " << green_bold << weather_temperature << endl
	 *  		<< cyan << ":	" << white_bold << "Weather" << cyan << " = " << green_bold << weather_conditions << endl
	 *  		<< cyan << ":	 " << white_bold << "Sky" << cyan << " = " << green_bold << weather_sky_conditions << endl;
	 *
	 *  cout << cyan << ":=:=:=:=:=:=:=:=:=:=:=:=:=:=[ " << red_bold << custom_header << cyan << " ]=:=:=:=:=:=:=:=:=:=:=:=:=:=:" << endl
	 *  		<< cyan << ":    " << white_bold << custom_command << cyan << " = " << green_bold << custom_command_output << endl;
	 *
	 *  cout << cyan << ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:[]:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:"
	 *  		<< color_default << endl << endl; */

	//Stable output
	cout << cyan << "Dynamic-MOTD-CPP" << color_default << endl;
	cout	<< "Date/Time:	" << datetime 				<< endl
			<< "Hostname:	" << hostname 				<< endl
			<< "WLAN IP:	" << wlan_ip				<< endl
			<< "LAN IP:		" << lan_ip					<< endl
			<< "Kernel:		" << kernel_version			<< endl
			<< "Memory:		" << ram_size				<< " MB" << endl
			<< "Stats:		" << user_stats				<< endl;

	cout	<< "Username:	" << username				<< endl
			<< "Last Login:	" << last_login				<< endl
			<< "Home:		" << home_path				<< endl
			<< "Processes:	" << process_count			<< " of " << process_limit << endl;

	cout 	<< "Location:	" << weather_location		<< ", " << weather_zip << endl
			<< "Temp:		" << weather_temperature	<< endl
			<< "Weather:	" << weather_conditions		<< endl
			<< "Sky:		" << weather_sky_conditions	<< endl;

	//ncurses testing output
	initscr();
	printw("Hostname:	");
	printw(hostname);
	refresh();
	getch();
	endwin();
	return 0;
}
