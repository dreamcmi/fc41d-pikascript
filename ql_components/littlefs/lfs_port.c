#include "lfs_port.h"

static int lfs_port_read(const struct lfs_config* lfsc,
                         lfs_block_t block,
                         lfs_off_t off,
                         void* buffer,
                         lfs_size_t size) {
    ql_errcode_flash_e err = 0;
    err = ql_flash_parttion_read(QL_PARTITION_USR_RESERVE,
                                 (block * lfsc->block_size + off),
                                 (uint8_t*)buffer, size);
    if (err == QL_FLASH_SUCCESS) {
        return LFS_ERR_OK;
    } else {
        os_printf("Err: lfs_port_read faild %d\n", err);
        return LFS_ERR_IO;
    }
}

static int lfs_port_prog(const struct lfs_config* lfsc,
                         lfs_block_t block,
                         lfs_off_t off,
                         const void* buffer,
                         lfs_size_t size) {
    ql_errcode_flash_e err = 0;
    ql_flash_set_security(QL_FLASH_PROTECT_NONE);
    err = ql_flash_parttion_write(QL_PARTITION_USR_RESERVE,
                                  (block * lfsc->block_size + off),
                                  (uint8_t*)buffer, size);
    // ql_flash_set_security(QL_FLASH_UNPROTECT_LAST_BLOCK);
    if (err == QL_FLASH_SUCCESS) {
        return LFS_ERR_OK;
    } else {
        os_printf("Err: lfs_port_prog faild %d\n", err);
        return LFS_ERR_IO;
    }
}

static int lfs_port_erase(const struct lfs_config* lfsc, lfs_block_t block) {
    ql_errcode_flash_e err = 0;
    ql_flash_set_security(QL_FLASH_PROTECT_NONE);
    err = ql_flash_parttion_erase(QL_PARTITION_USR_RESERVE,
                                  block * lfsc->block_size, 4096);
    // ql_flash_set_security(QL_FLASH_UNPROTECT_LAST_BLOCK);
    if (err == QL_FLASH_SUCCESS) {
        return LFS_ERR_OK;
    } else {
        os_printf("Err: lfs_port_erase faild %d\n", err);
        return LFS_ERR_IO;
    }
}

static int lfs_port_sync(const struct lfs_config* lfsc) {
    return LFS_ERR_OK;
}

const struct lfs_config cfg = {
    .context = NULL,
    .read = lfs_port_read,
    .prog = lfs_port_prog,
    .erase = lfs_port_erase,
    .sync = lfs_port_sync,

    .read_size = 256,
    .prog_size = 256,
    .block_size = 4096,
    .block_count = 223,
    .cache_size = 256,
    .block_cycles = 32,
    .lookahead_size = 32,
};

lfs_t lfs_flash = {0};

int lfs_ll_mount() {
    int err = lfs_mount(&lfs_flash, &cfg);
    if (err != LFS_ERR_OK) {
        lfs_format(&lfs_flash, &cfg);
        lfs_mount(&lfs_flash, &cfg);
    }
    return err;
}

int lfs_ls(lfs_t* lfs, const char* path) {
    lfs_dir_t dir;
    int err = lfs_dir_open(lfs, &dir, path);
    if (err) {
        return err;
    }

    struct lfs_info info;
    while (true) {
        int res = lfs_dir_read(lfs, &dir, &info);
        if (res < 0) {
            return res;
        }

        if (res == 0) {
            break;
        }

        switch (info.type) {
            case LFS_TYPE_REG:
                os_printf("reg ");
                break;
            case LFS_TYPE_DIR:
                os_printf("dir ");
                break;
            default:
                os_printf("?   ");
                break;
        }

        static const char* prefixes[] = {"", "K", "M", "G"};
        for (int i = sizeof(prefixes) / sizeof(prefixes[0]) - 1; i >= 0; i--) {
            if (info.size >= (1 << 10 * i) - 1) {
                os_printf("%*u%sB ", 4 - (i != 0), info.size >> 10 * i,
                          prefixes[i]);
                break;
            }
        }

        os_printf("%s\n", info.name);
    }

    err = lfs_dir_close(lfs, &dir);
    if (err) {
        return err;
    }

    return 0;
}
