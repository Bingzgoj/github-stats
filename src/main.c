#include "config.h"
#include "stats.h"
#include "svg_writer.h"
#include "log.h"

#include <curl/curl.h>
#include <stdio.h>

int main(void)
{
    AppConfig cfg;
    if (load_config(&cfg) != 0) {
        return 1;
    }

    log_info("starting stats generation for user=%s (count_forks=%d)", cfg.user, cfg.count_forks);

    curl_global_init(CURL_GLOBAL_DEFAULT);

    GitStats stats;
    if (build_stats(cfg.user, cfg.token, cfg.count_forks, &stats) != 0) {
        log_error("failed to collect GitHub stats for user=%s", cfg.user);
        curl_global_cleanup();
        return 1;
    }

    if (write_svgs(&stats) != 0) {
        log_error("failed to write SVG output");
        curl_global_cleanup();
        return 1;
    }

    log_info("completed stats generation: repos=%lld stars=%lld forks=%lld languages=%zu",
             stats.repos,
             stats.stars,
             stats.forks,
             stats.lang_count);

    printf("generated/overview.svg\n");
    printf("generated/languages.svg\n");

    curl_global_cleanup();
    return 0;
}
