// Copyright 2022 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_FIRST_PARTY_SETS_FIRST_PARTY_SET_ENTRY_H_
#define NET_FIRST_PARTY_SETS_FIRST_PARTY_SET_ENTRY_H_

#include "net/base/net_export.h"
#include "net/base/schemeful_site.h"

namespace net {

// These values are persisted to DB. Entries should not be renumbered and
// numeric values should never be reused.
enum class SiteType {
  // The First-Party Set declaration listed this site as the "primary" site for
  // the set.
  kPrimary = 0,
  // The First-Party Set declaration listed this site as an associated site in
  // the set.
  kAssociated = 1,
  // The First-Party Set declaration listed this site as a service site in the
  // set.
  kService = 2,

  // Update FirstPartySetEntry::DeserializeSiteType if new SiteType is added.
};

// This class bundles together metadata associated with an entry in a
// First-Party Set.
class NET_EXPORT FirstPartySetEntry {
 public:
  FirstPartySetEntry();
  // `primary` is the primary site in the First-Party Set associated with this
  // entry.
  FirstPartySetEntry(SchemefulSite primary, SiteType site_type);

  FirstPartySetEntry(const FirstPartySetEntry&);
  FirstPartySetEntry& operator=(const FirstPartySetEntry&);
  FirstPartySetEntry(FirstPartySetEntry&&);
  FirstPartySetEntry& operator=(FirstPartySetEntry&&);

  ~FirstPartySetEntry();

  bool operator==(const FirstPartySetEntry& other) const;
  bool operator!=(const FirstPartySetEntry& other) const;

  static std::optional<net::SiteType> DeserializeSiteType(int value);

  std::string GetDebugString() const;

  const SchemefulSite& primary() const { return primary_; }

  SiteType site_type() const { return site_type_; }

 private:
  // The primary site associated with this site's set.
  SchemefulSite primary_;
  // The type associated with this site.
  SiteType site_type_;
};

NET_EXPORT std::ostream& operator<<(std::ostream& os,
                                    const FirstPartySetEntry& fpse);

}  // namespace net

#endif  // NET_FIRST_PARTY_SETS_FIRST_PARTY_SET_ENTRY_H_
