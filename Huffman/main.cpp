#include <bits/stdc++.h>

FILE *f;
FILE *g;

struct Forest {
    long long weight;
    long long root;
    unsigned char symb;
};

struct Tree {
    long long left, right, parent;
    unsigned char symb;
    long long v = 0;
    std::string code;
};

Forest forest[256];
Tree tree[512];
long long size_forest;
long long size_tree;
long long freq[256] = {0};


void min_min(long long &pos1, long long &pos2) {
    long long i = 2;
    pos1 = 0;
    pos2 = 1;
    long long min1 = forest[0].weight;
    long long min2 = forest[1].weight;
    while (forest[i].weight != 0 && size_forest >= i) {
        if (std::max(min1, min2) == min1 and min1 > forest[i].weight) {
            min1 = forest[i].weight;
            pos1 = i;
        } else if (std::max(min1, min2) == min2 and min2 > forest[i].weight) {
            min2 = forest[i].weight;
            pos2 = i;
        }
        i++;
    }
    long long tmp = pos1;
    if (std::min(min1, min2) == min2) {
        pos1 = pos2;
        pos2 = tmp;
    }
}

void create_tree1(FILE *f) {
    long long pos1, pos2;
    size_forest = 0;
    unsigned char ch;
    while (fscanf(f, "%c", &ch) != -1) {
        freq[ch]++;
    }
    for (long long i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            forest[size_forest].weight = freq[i];
            forest[size_forest].root = size_forest;
            forest[size_forest].symb = i;
            size_forest++;
        }
    }
    size_tree = size_forest;
    size_forest -= 1;
    for (long long i = 0; i < size_tree; i++) {
        tree[i].left = -1;
        tree[i].right = -1;
        tree[i].parent = -1;
        tree[i].code = "";
        tree[i].symb = forest[i].symb;
    }
    while (size_forest > 0) {
        min_min(pos1, pos2);
        tree[size_tree].left = forest[pos1].root;
        tree[size_tree].right = forest[pos2].root;
        tree[size_tree].parent = -1;
        tree[forest[pos1].root].parent = size_tree;
        tree[forest[pos2].root].parent = size_tree;
        forest[pos1].weight = forest[pos1].weight + forest[pos2].weight;
        forest[pos1].root = size_tree;
        forest[pos2].weight = forest[size_forest].weight;
        forest[pos2].root = forest[size_forest].root;
        size_tree++;
        size_forest--;
    }
}

long long create_codes1(long long root, std::string code) {
    if (tree[root].left == -1 && tree[root].right == -1) {
        tree[root].code = code;
        tree[root].v = 1;
        return tree[root].parent;
    }
    if (tree[root].right != -1 && tree[tree[root].right].v != 1) {
        code += '1';
        create_codes1(tree[root].right, code);
    }
    if (tree[tree[root].right].v == 1 && tree[tree[root].left].v == 0) {
        code.erase(code.size() - 1);
    }
    if (tree[root].left != -1 && tree[tree[root].left].v != 1) {
        code += '0';
        create_codes1(tree[root].left, code);
    }
    if (tree[tree[root].left].v == 1 && tree[tree[root].right].v == 1) {
        tree[root].v = 1;
        return tree[root].parent;
    }
}

std::string create_byte(std::string &ch, std::string &act, long long &cnt) {
    while (cnt != 8 && !act.empty()) {
        ch += act[0];
        cnt++;
        act.erase(0, 1);
    }
    return ch;
}

std::string beat_to_byte(std::string &ch, long long &cnt) {
    while (cnt != 8) {
        ch += "0";
        cnt++;
    }
    return ch;
}

void create_tree2(FILE *f) {
    long long pos1, pos2;
    char ch = 255;
    size_forest = 0;
    long long i = 0, tmp, j = 0;
    int flag = 0;
    std::string code, cnt = "";
    while (fscanf(f, "%c", &ch) && ch != ' ') {
        cnt += ch;
    }
    tmp = std::stoi(cnt);
    while (j < tmp) {
        j++;
        fscanf(f, "%c", &ch);
        if (flag == 0) {
            tree[i].symb = ch;
            flag = 1;
            continue;
        }
        if (ch == ' ' && flag == 1) {
            flag = 2;
            continue;
        }
        if (ch == ' ' && flag == 2) {
            freq[tree[i].symb] = std::stoi(code);
            flag = 0;
            code = "";
            i++;
        }
        if (flag == 2) {
            code += ch;
        }
    }
    for (long long i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            forest[size_forest].weight = freq[i];
            forest[size_forest].root = size_forest;
            size_forest++;
        }
    }
    size_tree = size_forest;
    size_forest -= 1;
    for (long long i = 0; i < size_tree; i++) {
        tree[i].left = -1;
        tree[i].right = -1;
        tree[i].parent = -1;
        tree[i].code = "";
    }
    while (size_forest > 0) {
        min_min(pos1, pos2);
        tree[size_tree].left = forest[pos1].root;
        tree[size_tree].right = forest[pos2].root;
        tree[size_tree].parent = -1;
        tree[forest[pos1].root].parent = size_tree;
        tree[forest[pos2].root].parent = size_tree;
        forest[pos1].weight = forest[pos1].weight + forest[pos2].weight;
        forest[pos1].root = size_tree;
        forest[pos2].weight = forest[size_forest].weight;
        forest[pos2].root = forest[size_forest].root;
        size_tree++;
        size_forest--;
    }
}

long long create_codes2(long long root, std::string code) {
    if (tree[root].left == -1 && tree[root].right == -1) {
        tree[root].code = code;
        tree[root].v = 1;
        return tree[root].parent;
    }
    if (tree[root].right != -1 && tree[tree[root].right].v != 1) {
        code += '1';
        create_codes2(tree[root].right, code);
    }
    if (tree[tree[root].right].v == 1 && tree[tree[root].left].v == 0) {
        code.erase(code.size() - 1);
    }
    if (tree[root].left != -1 && tree[tree[root].left].v != 1) {
        code += '0';
        create_codes2(tree[root].left, code);
    }
    if (tree[tree[root].left].v == 1 && tree[tree[root].right].v == 1) {
        tree[root].v = 1;
        return tree[root].parent;
    }
}

bool find_symb(std::string ch, long long i, long long root, char &symb) {
    if (i + 1 > ch.size() && tree[root].left != -1 && tree[root].right != -1) {
        return false;
    } else if (tree[root].left == -1 && tree[root].right == -1) {
        symb = tree[root].symb;
        return true;
    }
    if (ch[i] == '1') {
        return find_symb(ch, i + 1, tree[root].right, symb);
    } else if (ch[i] == '0') {
        return find_symb(ch, i + 1, tree[root].left, symb);
    }
}

void create_symb(std::string &act) {
    long long i = 0;
    std::string ch = "";
    char symb = '0';
    while (i != act.size() - 1) {
        ch += act[i];
        if (find_symb(ch, 0, size_tree - 1, symb)) {
            fprintf(g, "%c", symb);
            symb = '0';
            ch = "";
        }
        i++;
    }
}

int32_t main(int argc, char *argv[]) {
    if (!strcmp("encode", argv[1])) {
        unsigned char ch;
        std::string che = "";
        int i;
        long long cnt = 0;
        std::string act;
        std::vector<std::string> codes(256, "");
        f = fopen(argv[3], "rb");
        g = fopen(argv[2], "wb");
        create_tree1(f);
        create_codes1(size_tree - 1, "");
        i = 0;
        int size = 0;
        for (int ii = 0; ii < 256; ii++) {
            if (freq[ii]) {
                size += 3 + (std::to_string(freq[ii]).size());
            }
        }
        fprintf(g, "%d ", size);
        for (long long ii = 0; ii < 256; ii++) {
            if (freq[ii]) {
                fprintf(g, "%c %lld ", (unsigned char) ii, freq[ii]);
            }
        }
        i = 0;
        while (tree[i].code != "") {
            codes[tree[i].symb] = tree[i].code;
            i++;
        }
        rewind(f);
        while (fscanf(f, "%c", &ch) != -1) {
            act = codes[ch];
            while (!act.empty()) {
                create_byte(che, act, cnt);
                if (cnt == 8) {
                    fprintf(g, "%c", static_cast<unsigned char>(std::stoul(che, nullptr, 2)));
                    cnt = 0;
                    che = "";
                }
            }
        }
        if (cnt < 8 && feof(f) && cnt != 0) {
            long long con = cnt;
            fprintf(g, "%c", static_cast<unsigned char>(std::stoul(beat_to_byte(che, cnt), nullptr, 2)));
            fprintf(g, "%d", cnt - con);
            fprintf(g, "%c", '1');
        } else {
            fprintf(g, "%c", '0');
        }
        fclose(g);
    } else {
        f = fopen(argv[2], "rb");
        g = fopen(argv[3], "wb");
        unsigned char ch = '\000';
        unsigned char last = '\000';
        unsigned char pre_last = '\000';
        std::string act = "";
        create_tree2(f);
        create_codes2(size_tree - 1, "");
        while (fscanf(f, "%c", &ch) != -1) {
            act += std::bitset<8>(ch).to_string();
        }
        fseek(f, -1, SEEK_END);
        last = fgetc(f);
        fseek(f, -2, SEEK_END);
        pre_last = fgetc(f);
        if (last == '0') {
            for (int i = 1; i < 8; i++) {
                act.pop_back();
            }
            create_symb(act);
        }
        if (last == '1') {
            for (int i = 1; i < pre_last - '0' + 16; i++) {
                act.pop_back();
            }
            create_symb(act);
        }
    }
}
