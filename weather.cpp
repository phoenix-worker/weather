#include <curl/curl.h>

static const char *url = 	"https://ru.wttr.in/Magnitogorsk"
							"?format=%C\\n"
							"Температура:+%t%20Ветер:+%w\\n"
							"Влажность:+%h%20Давление:+%P\\n";

void appendTimeInfo(FILE *file);

int main() {
	CURL *handle;
	handle = curl_easy_init();
	if (handle) {
		FILE *file = fopen("./forecast.temp", "w");
		curl_easy_setopt(handle, CURLOPT_URL, url);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)file);
		curl_easy_setopt(handle, CURLOPT_TIMEOUT, 10);
		CURLcode result = curl_easy_perform(handle);
		if (result == CURLE_OK) {
			// Запрос выполнен успешно
			appendTimeInfo(file);
			fclose(file);
			remove("forecast");
			rename("./forecast.temp", "forecast");
		} else {
			// Не удалось выполнить запрос
			fclose(file);
			remove("./forecast.temp");
		}
		curl_easy_cleanup(handle);
	}
}

void appendTimeInfo(FILE *file) {
	time_t epochTime;
	time(&epochTime);
	struct tm *timeInfo;
	timeInfo = localtime(&epochTime);
	int BUFF_SIZE = 100;
	char buffer[BUFF_SIZE];
	strftime(buffer, BUFF_SIZE, "Обновлено в %H:%M %e.%m.%G\n", timeInfo);
	fputs(buffer, file);
}
