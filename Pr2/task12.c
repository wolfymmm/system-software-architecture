#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <elf.h>
#include <stdlib.h>


void printk(const char* msg) {
    fputs(msg, stderr);
}

int is_image_valid(Elf32_Ehdr *hdr) {
    return (memcmp(hdr->e_ident, ELFMAG, SELFMAG) == 0);
}

void* load_elf_image(char *elf_start, unsigned int size) {
    Elf32_Ehdr *hdr = (Elf32_Ehdr *) elf_start;
    Elf32_Phdr *phdr;
    char *start, *taddr;

    if (!is_image_valid(hdr)) {
        printk("Invalid ELF image\n");
        return NULL;
    }

    char *exec = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if (!exec) {
        printk("Memory allocation error\n");
        return NULL;
    }
    memset(exec, 0, size);

    phdr = (Elf32_Phdr *)(elf_start + hdr->e_phoff);
    for (int i = 0; i < hdr->e_phnum; ++i) {
        if (phdr[i].p_type == PT_LOAD) {
            start = elf_start + phdr[i].p_offset;
            taddr = exec + phdr[i].p_vaddr;
            memmove(taddr, start, phdr[i].p_filesz);

            if (!(phdr[i].p_flags & PF_W)) {
                mprotect(taddr, phdr[i].p_memsz, PROT_READ);
            }
            if (phdr[i].p_flags & PF_X) {
                mprotect(taddr, phdr[i].p_memsz, PROT_EXEC);
            }
        }
    }

    return exec + hdr->e_entry;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ELF file>\n", argv[0]);
        return 1;
    }

    FILE *elf_file = fopen(argv[1], "rb");
    if (!elf_file) {
        perror("Error opening ELF file");
        return 1;
    }

    fseek(elf_file, 0, SEEK_END);
    unsigned int size = ftell(elf_file);
    fseek(elf_file, 0, SEEK_SET);
    char *buf = malloc(size);
    fread(buf, 1, size, elf_file);
    fclose(elf_file);

    void (*entry_point)(void) = load_elf_image(buf, size);
    if (!entry_point) {
        free(buf);
        return 1;
    }

    entry_point();
    free(buf);
    return 0;
}
