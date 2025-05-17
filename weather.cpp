#include <curl/curl.h>

static const char *url = 	"https://ru.wttr.in/Magnitogorsk"
							"?format=%C\\n"
							"Температура:+%t%20Ветер:+%w\\n"
							"Влажность:+%h%20Давление:+%P\\n";

int main() {
	CURL *handle;
	handle = curl_easy_init();
	if (handle) {
		curl_easy_setopt(handle, CURLOPT_URL, url);
		curl_easy_perform(handle);
		curl_easy_cleanup(handle);
	}
}
