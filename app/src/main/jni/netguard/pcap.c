/*
    This file is part of NetGuard.

    NetGuard is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    NetGuard is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with NetGuard.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2015-2016 by Marcel Bokhorst (M66B)
*/

#include "netguard.h"

FILE *pcap_file = NULL;
FILE *pcap_file_udp = NULL;
FILE *pcap_file_tcp = NULL;
FILE *pcap_file_ip = NULL;
FILE *pcap_file_port = NULL;

void write_pcap_hdr() {
    struct pcap_hdr_s pcap_hdr;
    pcap_hdr.magic_number = 0xa1b2c3d4;
    pcap_hdr.version_major = 2;
    pcap_hdr.version_minor = 4;
    pcap_hdr.thiszone = 0;
    pcap_hdr.sigfigs = 0;
    pcap_hdr.snaplen = MAX_PCAP_RECORD;
    pcap_hdr.network = LINKTYPE_RAW;
    write_pcap(&pcap_hdr, sizeof(struct pcap_hdr_s));
}

void write_pcap_hdr_udp() {
    struct pcap_hdr_s pcap_hdr;
    pcap_hdr.magic_number = 0xa1b2c3d4;
    pcap_hdr.version_major = 2;
    pcap_hdr.version_minor = 4;
    pcap_hdr.thiszone = 0;
    pcap_hdr.sigfigs = 0;
    pcap_hdr.snaplen = MAX_PCAP_RECORD;
    pcap_hdr.network = LINKTYPE_RAW;
    write_pcap_udp(&pcap_hdr, sizeof(struct pcap_hdr_s));
}

void write_pcap_hdr_tcp() {
    struct pcap_hdr_s pcap_hdr;
    pcap_hdr.magic_number = 0xa1b2c3d4;
    pcap_hdr.version_major = 2;
    pcap_hdr.version_minor = 4;
    pcap_hdr.thiszone = 0;
    pcap_hdr.sigfigs = 0;
    pcap_hdr.snaplen = MAX_PCAP_RECORD;
    pcap_hdr.network = LINKTYPE_RAW;
    write_pcap_tcp(&pcap_hdr, sizeof(struct pcap_hdr_s));
}

void write_pcap_hdr_ip() {
    struct pcap_hdr_s pcap_hdr;
    pcap_hdr.magic_number = 0xa1b2c3d4;
    pcap_hdr.version_major = 2;
    pcap_hdr.version_minor = 4;
    pcap_hdr.thiszone = 0;
    pcap_hdr.sigfigs = 0;
    pcap_hdr.snaplen = MAX_PCAP_RECORD;
    pcap_hdr.network = LINKTYPE_RAW;
    write_pcap_ip(&pcap_hdr, sizeof(struct pcap_hdr_s));
}

void write_pcap_hdr_port() {
    struct pcap_hdr_s pcap_hdr;
    pcap_hdr.magic_number = 0xa1b2c3d4;
    pcap_hdr.version_major = 2;
    pcap_hdr.version_minor = 4;
    pcap_hdr.thiszone = 0;
    pcap_hdr.sigfigs = 0;
    pcap_hdr.snaplen = MAX_PCAP_RECORD;
    pcap_hdr.network = LINKTYPE_RAW;
    write_pcap_port(&pcap_hdr, sizeof(struct pcap_hdr_s));
}

void write_pcap_rec(const uint8_t *buffer, size_t length) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts))
        log_android(ANDROID_LOG_ERROR, "clock_gettime error %d: %s", errno, strerror(errno));

    size_t plen = (length < MAX_PCAP_RECORD ? length : MAX_PCAP_RECORD);
    struct pcaprec_hdr_s pcap_rec;

    pcap_rec.ts_sec = (guint32_t) ts.tv_sec;
    pcap_rec.ts_usec = (guint32_t) (ts.tv_nsec / 1000);
    pcap_rec.incl_len = (guint32_t) plen;
    pcap_rec.orig_len = (guint32_t) length;

    write_pcap(&pcap_rec, sizeof(struct pcaprec_hdr_s));
    write_pcap(buffer, plen);
}

void write_pcap_rec_udp(const uint8_t *buffer, size_t length) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts))
        log_android(ANDROID_LOG_ERROR, "clock_gettime error %d: %s", errno, strerror(errno));

    size_t plen = (length < MAX_PCAP_RECORD ? length : MAX_PCAP_RECORD);
    struct pcaprec_hdr_s pcap_rec;

    pcap_rec.ts_sec = (guint32_t) ts.tv_sec;
    pcap_rec.ts_usec = (guint32_t) (ts.tv_nsec / 1000);
    pcap_rec.incl_len = (guint32_t) plen;
    pcap_rec.orig_len = (guint32_t) length;

    write_pcap_udp(&pcap_rec, sizeof(struct pcaprec_hdr_s));
    write_pcap_udp(buffer, plen);
}

void write_pcap_rec_tcp(const uint8_t *buffer, size_t length) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts))
        log_android(ANDROID_LOG_ERROR, "clock_gettime error %d: %s", errno, strerror(errno));

    size_t plen = (length < MAX_PCAP_RECORD ? length : MAX_PCAP_RECORD);
    struct pcaprec_hdr_s pcap_rec;

    pcap_rec.ts_sec = (guint32_t) ts.tv_sec;
    pcap_rec.ts_usec = (guint32_t) (ts.tv_nsec / 1000);
    pcap_rec.incl_len = (guint32_t) plen;
    pcap_rec.orig_len = (guint32_t) length;

    write_pcap_tcp(&pcap_rec, sizeof(struct pcaprec_hdr_s));
    write_pcap_tcp(buffer, plen);
}

void write_pcap_rec_ip(const uint8_t *buffer, size_t length) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts))
        log_android(ANDROID_LOG_ERROR, "clock_gettime error %d: %s", errno, strerror(errno));

    size_t plen = (length < MAX_PCAP_RECORD ? length : MAX_PCAP_RECORD);
    struct pcaprec_hdr_s pcap_rec;

    pcap_rec.ts_sec = (guint32_t) ts.tv_sec;
    pcap_rec.ts_usec = (guint32_t) (ts.tv_nsec / 1000);
    pcap_rec.incl_len = (guint32_t) plen;
    pcap_rec.orig_len = (guint32_t) length;

    write_pcap_ip(&pcap_rec, sizeof(struct pcaprec_hdr_s));
    write_pcap_ip(buffer, plen);
}

void write_pcap_rec_port(const uint8_t *buffer, size_t length) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts))
        log_android(ANDROID_LOG_ERROR, "clock_gettime error %d: %s", errno, strerror(errno));

    size_t plen = (length < MAX_PCAP_RECORD ? length : MAX_PCAP_RECORD);
    struct pcaprec_hdr_s pcap_rec;

    pcap_rec.ts_sec = (guint32_t) ts.tv_sec;
    pcap_rec.ts_usec = (guint32_t) (ts.tv_nsec / 1000);
    pcap_rec.incl_len = (guint32_t) plen;
    pcap_rec.orig_len = (guint32_t) length;

    write_pcap_port(&pcap_rec, sizeof(struct pcaprec_hdr_s));
    write_pcap_port(buffer, plen);
}


void write_pcap(const void *ptr, size_t len) {
    if (fwrite(ptr, len, 1, pcap_file) < 1)
        log_android(ANDROID_LOG_ERROR, "PCAP fwrite error %d: %s", errno, strerror(errno));
    else {
        long fsize = ftell(pcap_file);
        log_android(ANDROID_LOG_VERBOSE, "PCAP wrote %d @%ld", len, fsize);

        if (fsize > MAX_PCAP_FILE) {
            log_android(ANDROID_LOG_WARN, "PCAP truncate @%ld", fsize);
            if (ftruncate(fileno(pcap_file), sizeof(struct pcap_hdr_s)))
                log_android(ANDROID_LOG_ERROR, "PCAP ftruncate error %d: %s",
                            errno, strerror(errno));
            else {
                if (!lseek(fileno(pcap_file), sizeof(struct pcap_hdr_s), SEEK_SET))
                    log_android(ANDROID_LOG_ERROR, "PCAP ftruncate error %d: %s",
                                errno, strerror(errno));
            }
        }
    }
}

void write_pcap_udp(const void *ptr, size_t len) {
    if (fwrite(ptr, len, 1, pcap_file_udp) < 1)
        log_android(ANDROID_LOG_ERROR, "PCAP fwrite error %d: %s", errno, strerror(errno));
    else {
        long fsize = ftell(pcap_file_udp);
        log_android(ANDROID_LOG_VERBOSE, "PCAP wrote %d @%ld", len, fsize);

        if (fsize > MAX_PCAP_FILE) {
            log_android(ANDROID_LOG_WARN, "PCAP truncate @%ld", fsize);
            if (ftruncate(fileno(pcap_file_udp), sizeof(struct pcap_hdr_s)))
                log_android(ANDROID_LOG_ERROR, "PCAP ftruncate error %d: %s",
                            errno, strerror(errno));
            else {
                if (!lseek(fileno(pcap_file_udp), sizeof(struct pcap_hdr_s), SEEK_SET))
                    log_android(ANDROID_LOG_ERROR, "PCAP ftruncate error %d: %s",
                                errno, strerror(errno));
            }
        }
    }
}

void write_pcap_tcp(const void *ptr, size_t len) {
    if (fwrite(ptr, len, 1, pcap_file_tcp) < 1)
        log_android(ANDROID_LOG_ERROR, "PCAP fwrite error %d: %s", errno, strerror(errno));
    else {
        long fsize = ftell(pcap_file_tcp);
        log_android(ANDROID_LOG_VERBOSE, "PCAP wrote %d @%ld", len, fsize);

        if (fsize > MAX_PCAP_FILE) {
            log_android(ANDROID_LOG_WARN, "PCAP truncate @%ld", fsize);
            if (ftruncate(fileno(pcap_file_tcp), sizeof(struct pcap_hdr_s)))
                log_android(ANDROID_LOG_ERROR, "PCAP ftruncate error %d: %s",
                            errno, strerror(errno));
            else {
                if (!lseek(fileno(pcap_file_tcp), sizeof(struct pcap_hdr_s), SEEK_SET))
                    log_android(ANDROID_LOG_ERROR, "PCAP ftruncate error %d: %s",
                                errno, strerror(errno));
            }
        }
    }
}

void write_pcap_ip(const void *ptr, size_t len) {
    if (fwrite(ptr, len, 1, pcap_file_ip) < 1)
        log_android(ANDROID_LOG_ERROR, "PCAP fwrite error %d: %s", errno, strerror(errno));
    else {
        long fsize = ftell(pcap_file_ip);
        log_android(ANDROID_LOG_VERBOSE, "PCAP wrote %d @%ld", len, fsize);

        if (fsize > MAX_PCAP_FILE) {
            log_android(ANDROID_LOG_WARN, "PCAP truncate @%ld", fsize);
            if (ftruncate(fileno(pcap_file_ip), sizeof(struct pcap_hdr_s)))
                log_android(ANDROID_LOG_ERROR, "PCAP ftruncate error %d: %s",
                            errno, strerror(errno));
            else {
                if (!lseek(fileno(pcap_file_ip), sizeof(struct pcap_hdr_s), SEEK_SET))
                    log_android(ANDROID_LOG_ERROR, "PCAP ftruncate error %d: %s",
                                errno, strerror(errno));
            }
        }
    }
}

void write_pcap_port(const void *ptr, size_t len) {
    if (fwrite(ptr, len, 1, pcap_file_port) < 1)
        log_android(ANDROID_LOG_ERROR, "PCAP fwrite error %d: %s", errno, strerror(errno));
    else {
        long fsize = ftell(pcap_file_port);
        log_android(ANDROID_LOG_VERBOSE, "PCAP wrote %d @%ld", len, fsize);

        if (fsize > MAX_PCAP_FILE) {
            log_android(ANDROID_LOG_WARN, "PCAP truncate @%ld", fsize);
            if (ftruncate(fileno(pcap_file_port), sizeof(struct pcap_hdr_s)))
                log_android(ANDROID_LOG_ERROR, "PCAP ftruncate error %d: %s",
                            errno, strerror(errno));
            else {
                if (!lseek(fileno(pcap_file_port), sizeof(struct pcap_hdr_s), SEEK_SET))
                    log_android(ANDROID_LOG_ERROR, "PCAP ftruncate error %d: %s",
                                errno, strerror(errno));
            }
        }
    }
}