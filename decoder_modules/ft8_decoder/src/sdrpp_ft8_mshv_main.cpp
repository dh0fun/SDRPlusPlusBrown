#include <core.h>
#include <iostream>
#include <stdio.h>
#include <module.h>
#include <ctm.h>
#include <utils/wav.h>
#include <utils/riff.h>
#include "dsp/types.h"
#include "dsp/multirate/polyphase_resampler.h"
#include "dsp/multirate/rational_resampler.h"

#include "ft8_etc/mshv_support.h"
#include "ft8_etc/mscore.h"
#include "ft8_etc/decoderms.h"

extern void doDecode(const char *mode, const char *path, std::function<void(int mode, std::vector<std::string> result)> callback);

static void help(const char *cmd) {
    fprintf(stderr,"usage: %s --decode <path> [--mode <mode>]\n", cmd);
    exit(1);
}

int main(int argc, char* argv[]) {
    std::string decodeFile;
    std::string mode = "ft8";
    for(int i=1; i<argc; i++) {
        if (!strcmp(argv[i],"--decode")) {
            i++;
            if (i < argc) {
                decodeFile = argv[i];
            }
        }
        if (!strcmp(argv[i],"--mode")) {
            i++;
            if (i < argc) {
                mode = argv[i];
            }
        }
    }
    if (decodeFile == "") {
        fprintf(stderr, "ERROR: wav file for decode is not specified\n");
        help(argv[0]);
    }
    if (mode == "ft8" || mode == "ft4") {
        fprintf(stdout, "Using mode: %s\n", mode.c_str());
        fprintf(stdout, "Using file: %s\n", decodeFile.c_str());
        doDecode(mode.c_str(), decodeFile.c_str(), [](int mode, std::vector<std::string> result) {
        });
        exit(0);
    } else {
        fprintf(stderr, "ERROR: invalid mode is specified. Valid modes: ft8, ft4\n");
        exit(1);
    }
}