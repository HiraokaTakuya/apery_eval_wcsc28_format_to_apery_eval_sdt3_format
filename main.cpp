/*
  Copyright (C) 2018 Hiraoka Takuya

  This is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cinttypes>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "drag & drop apery eval dir" << std::endl;
        return 0;
    }
    std::string dir = std::string(argv[1]);
    { // KPP
        std::ifstream ifs((dir + "/KPP.bin").c_str(), std::ios::binary);
        const size_t fileSize = static_cast<size_t>(ifs.seekg(0, std::ios::end).tellg());
        ifs.seekg(0, std::ios::beg); // ストリームのポインタを一番前に戻して、これから先で使いやすいようにする
        std::vector<char> buf(fileSize);
        std::vector<char> outbuf(buf.size());
        ifs.read(reinterpret_cast<char*>(buf.data()), fileSize);
        std::copy(std::begin(buf), std::end(buf), std::begin(outbuf));
        std::ofstream ofs((dir + "/KPP_synthesized.bin").c_str(), std::ios::binary);
        ofs.write(reinterpret_cast<char*>(outbuf.data()), outbuf.size() * sizeof(char));
    }
    { // KKP
        std::ifstream ifs((dir + "/KKP.bin").c_str(), std::ios::binary);
        const size_t fileSize = static_cast<size_t>(ifs.seekg(0, std::ios::end).tellg());
        ifs.seekg(0, std::ios::beg); // ストリームのポインタを一番前に戻して、これから先で使いやすいようにする
        std::vector<int16_t> buf(fileSize/sizeof(int16_t));
        std::vector<int32_t> outbuf(buf.size());
        ifs.read(reinterpret_cast<char*>(buf.data()), fileSize);
        std::copy(std::begin(buf), std::end(buf), std::begin(outbuf));
        std::ofstream ofs((dir + "/KKP_synthesized.bin").c_str(), std::ios::binary);
        ofs.write(reinterpret_cast<char*>(outbuf.data()), outbuf.size() * sizeof(int32_t));
    }
    { // KK
        std::vector<char> outbuf(81*81*4);
        std::fill(std::begin(outbuf), std::end(outbuf), 0);
        std::ofstream ofs((dir + "/KK_synthesized.bin").c_str(), std::ios::binary);
        ofs.write(reinterpret_cast<char*>(outbuf.data()), outbuf.size() * sizeof(char));
    }
}
