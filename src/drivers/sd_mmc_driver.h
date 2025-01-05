#pragma once

#include <SD_MMC.h>

void init_sd_mmc();

void list_files_in_sd_mmc(const char *path = "/");
