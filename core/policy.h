// Copyright (c) 2015 Vijos Dev Team. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINC_CORE_POLICY_H_
#define WINC_CORE_POLICY_H_

#include <Windows.h>
#include <memory>
#include <vector>

#include "core/sid.h"
#include "core/desktop.h"

namespace winc {

class Policy {
public:
  Policy()
    : use_alternate_desktop_(false)
    , disable_max_privilege_(false)
    {}

  void UseAlternateDesktop() {
    use_alternate_desktop_ = true;
  }

  void DisableMaxPrivilege() {
    disable_max_privilege_ = true;
  }

  ResultCode GetSidLogonSession(Sid *out_sid);

  ResultCode RestrictSid(WELL_KNOWN_SID_TYPE type);
  void RestrictSid(const Sid &sid);

  ResultCode CreateRestrictedToken(HANDLE *out_token);
  ResultCode CreateTargetDesktop(Desktop **out_desktop);

private:
  bool CreateEffectiveToken(HANDLE *out_token);

private:
  bool use_alternate_desktop_;
  bool disable_max_privilege_;
  std::vector<Sid> restricted_sids_;
};

}

#endif
