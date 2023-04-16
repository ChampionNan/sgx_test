#pragma once

#include <string.h>
#include <limits.h>

#define PAYLOAD 29 // 1, 29

struct EncOneBlock {
  int sortKey;    // used for sorting 
  int primaryKey; // tie-breaker when soryKey equals
  int payLoad[PAYLOAD];
  int randomKey;  // salt for encryption, representative for iv

  EncOneBlock() {
    sortKey = -1;
  }
  friend EncOneBlock operator*(const bool &flag, const EncOneBlock &y) {
    EncOneBlock res;
    res.sortKey = flag * y.sortKey;
    res.primaryKey = flag * y.primaryKey;
    // res.payLoad = flag * y.payLoad;
    for (int i = 0; i < PAYLOAD; ++i) {
      res.payLoad[i] = flag * y.payLoad[i];
    }
    res.randomKey = flag * y.randomKey;
    return res;
  }
  friend EncOneBlock operator+(const EncOneBlock &x, const EncOneBlock &y) {
    EncOneBlock res;
    res.sortKey = x.sortKey + y.sortKey;
    res.primaryKey = x.primaryKey + y.primaryKey;
    // res.payLoad = x.payLoad + y.payLoad;
    for (int i = 0; i < PAYLOAD; ++i) {
      res.payLoad[i] = x.payLoad[i] + y.payLoad[i];
    }
    res.randomKey = x.randomKey + y.randomKey;
    return res;
  }
  friend EncOneBlock operator^(const EncOneBlock &x, const EncOneBlock &y) {
    EncOneBlock res;
    res.sortKey = x.sortKey ^ y.sortKey;
    res.primaryKey = x.primaryKey ^ y.primaryKey;
    for (int i = 0; i < PAYLOAD; ++i) {
      res.payLoad[i] = x.payLoad[i] ^ y.payLoad[i];
    }
    res.randomKey = x.randomKey ^ y.randomKey;
    return res;
  }
  friend EncOneBlock operator&(const EncOneBlock &x, const int &mask) {
    EncOneBlock res;
    res.sortKey = x.sortKey & mask;
    res.primaryKey = x.primaryKey & mask;
    for (int i = 0; i < PAYLOAD; ++i) {
      res.payLoad[i] = x.payLoad[i] & mask;
    }
    res.randomKey = x.randomKey & mask;
    return res;
  }
  friend bool operator<(const EncOneBlock &a, const EncOneBlock &b) {
    if (a.sortKey < b.sortKey) {
      return true;
    } else if (a.sortKey > b.sortKey) {
      return false;
    } else {
      if (a.primaryKey < b.primaryKey) {
        return true;
      } else if (a.primaryKey > b.primaryKey) {
        return false;
      }
    }
    return true; // equal
  }
  bool operator=(const EncOneBlock &a) {
    memcpy(this, &a, sizeof(EncOneBlock));
    return true;
  }
};