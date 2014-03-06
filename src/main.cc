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

int main() {
	
}

int init() {
	
}

int color_palette() {
	/* ASCII Character Colors
	 *		Color				ASCII Code
	 * =================================== */
	string  color_default		("\e[0;0m");
	string  red					("\e[0;31m");
	string  red_bold			("\e[1;31m");
	string  red_light			("\e[2;31m");
	string  red_italic			("\e[3;31m");
	string  red_underlined		("\e[4;31m");
	string  green				("\e[0;32m");
	string  green_bold			("\e[1;32m");
	string  green_light			("\e[2;32m");
	string  green_italic		("\e[3;32m");
	string  green_underlined	("\e[4;32m");
	string  yellow				("\e[0;33m");
	string  yellow_bold			("\e[1;33m");
	string  yellow_light		("\e[2;33m");
	string  yellow_italic		("\e[3;33m");
	string  yellow_underlined	("\e[4;33m");
	string  blue				("\e[0;34m");
	string  blue_bold			("\e[1;34m");
	string  blue_light			("\e[2;34m");
	string  blue_italic			("\e[3;34m");
	string  blue_underlined		("\e[4;34m");
	string  magenta				("\e[0;35m");
	string  magenta_bold		("\e[1;35m");
	string  magenta_light		("\e[2;35m");
	string  magenta_italic		("\e[3;35m");
	string  magenta_underlined	("\e[4;35m");
	string  cyan				("\e[0;36m");
	string  cyan_bold			("\e[1;36m");
	string  cyan_light			("\e[2;36m");
	string  cyan_italic			("\e[3;36m");
	string  cyan_underlined		("\e[4;36m");
	string  gray				("\e[0;37m");
	string  gray_bold			("\e[1;37m");
	string  gray_light			("\e[2;37m");
	string  gray_italic			("\e[3;37m");
	string  gray_underlined		("\e[4;37m");
	string  white				("\e[0;97m");
	string  white_bold			("\e[1;97m");
	string  white_light			("\e[2;97m");
	string  white_italic		("\e[3;97m");
	string  white_underlined	("\e[4;97m");
}

int get_stats() {

	struct utsname uname_info;
	uname(&uname_info);
	const double minute = 60;
	const double hour = minute * 60;
	const double day = hour * 24;
	const double megabyte = 1024 * 1024;
	struct sysinfo uname_system_info;
	sysinfo (&uname_system_info);

	time_t hex_time;
	time (&hex_time);
	string datetime = ctime(&hex_time);
	datetime.erase(std::remove(datetime.begin(), datetime.end(), '\n'), datetime.end());

	char hostname [128];
	gethostname(hostname, sizeof hostname);

	string wlan_ip;
	int wlan_ip_address;
	struct ifreq wlan_ip_address_numeric;
	wlan_ip_address = socket (AF_INET, SOCK_DGRAM, 0);
	wlan_ip_address_numeric.ifr_addr.sa_family = AF_INET;
	strncpy (wlan_ip_address_numeric.ifr_name, "wlan0", IFNAMSIZ-1);
	ioctl (wlan_ip_address, SIOCGIFADDR, &wlan_ip_address_numeric);
	close (wlan_ip_address);
	wlan_ip = inet_ntoa(((struct sockaddr_in *) &wlan_ip_address_numeric.ifr_addr) -> sin_addr);

	string lan_ip;
	int lan_ip_address;
	struct ifreq lan_ip_address_numeric;
	lan_ip_address = socket (AF_INET, SOCK_DGRAM, 0);
	lan_ip_address_numeric.ifr_addr.sa_family = AF_INET;
	strncpy (lan_ip_address_numeric.ifr_name, "eth0", IFNAMSIZ-1);
	ioctl (lan_ip_address, SIOCGIFADDR, &lan_ip_address_numeric);
	close (lan_ip_address);
	lan_ip = inet_ntoa(((struct sockaddr_in *) &lan_ip_address_numeric.ifr_addr) -> sin_addr);

	string kernel_version = uname_info.release;

	string ram_size = "RAM";

	string user_stats;
	user_stats = system("w | awk 'NR==1' | cut -c2-");
}

int get_users_stats () {

	struct utsname uname_info;
	uname(&uname_info);
	const double minute = 60;
	const double hour = minute * 60;
	const double day = hour * 24;
	const double megabyte = 1024 * 1024;
	struct sysinfo uname_system_info;
	sysinfo (&uname_system_info);

	string username = getenv("USER");

	string last_login;
	last_login = system("last -n 2 -R $USER | awk 'NR==2'");

	string home_path = getenv("HOME");

	string process_count;
	process_count = (uname_system_info.procs);

	string process_limit;
	process_limit = system("cat /proc/meminfo | grep MemTotal | awk {'print $2'}");
	
	return 0;
}

int get_weather () {
	string weather_location = "location";
	string weather_zip = "zip";

	string weather_temperature = "Temperature";

	string weather_conditions = "Weather conditions";

	string weather_sky_conditions = "Sky conditions";
}

int get_cutom_command () {
	string custom_header = "Custom Command Stats";
	string custom_title = "Custom Command";
	string custom_command;
	custom_command = system("echo Custom Command");
	string custom_command_output = custom_command;
}
