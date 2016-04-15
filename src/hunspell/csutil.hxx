/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Hunspell, based on MySpell.
 *
 * The Initial Developers of the Original Code are
 * Kevin Hendricks (MySpell) and Németh László (Hunspell).
 * Portions created by the Initial Developers are Copyright (C) 2002-2005
 * the Initial Developers. All Rights Reserved.
 *
 * Contributor(s): David Einstein, Davide Prina, Giuseppe Modugno,
 * Gianluca Turconi, Simon Brouwer, Noll János, Bíró Árpád,
 * Goldman Eleonóra, Sarlós Tamás, Bencsáth Boldizsár, Halácsy Péter,
 * Dvornik László, Gefferth András, Nagy Viktor, Varga Dániel, Chris Halls,
 * Rene Engelhard, Bram Moolenaar, Dafydd Jones, Harri Pitkänen
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
/*
 * Copyright 2002 Kevin B. Hendricks, Stratford, Ontario, Canada
 * And Contributors.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. All modifications to the source code must be clearly marked as
 *    such.  Binary redistributions based on modified source code
 *    must be clearly marked as modified versions in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY KEVIN B. HENDRICKS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * KEVIN B. HENDRICKS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef __CSUTILHXX__
#define __CSUTILHXX__

#include "hunvisapi.h"

// First some base level utility routines

#include <string>
#include <vector>
#include <string.h>
#include "w_char.hxx"
#include "htypes.hxx"

#ifdef MOZILLA_CLIENT
#include "nscore.h"  // for mozalloc headers
#endif

// casing
#define NOCAP 0
#define INITCAP 1
#define ALLCAP 2
#define HUHCAP 3
#define HUHINITCAP 4

// default encoding and keystring
#define SPELL_ENCODING "ISO8859-1"
#define SPELL_KEYSTRING "qwertyuiop|asdfghjkl|zxcvbnm"

// default morphological fields
#define MORPH_STEM "st:"
#define MORPH_ALLOMORPH "al:"
#define MORPH_POS "po:"
#define MORPH_DERI_PFX "dp:"
#define MORPH_INFL_PFX "ip:"
#define MORPH_TERM_PFX "tp:"
#define MORPH_DERI_SFX "ds:"
#define MORPH_INFL_SFX "is:"
#define MORPH_TERM_SFX "ts:"
#define MORPH_SURF_PFX "sp:"
#define MORPH_FREQ "fr:"
#define MORPH_PHON "ph:"
#define MORPH_HYPH "hy:"
#define MORPH_PART "pa:"
#define MORPH_FLAG "fl:"
#define MORPH_HENTRY "_H:"
#define MORPH_TAG_LEN strlen(MORPH_STEM)

#define MSEP_FLD ' '
#define MSEP_REC '\n'
#define MSEP_ALT '\v'

// default flags
#define DEFAULTFLAGS 65510
#define FORBIDDENWORD 65510
#define ONLYUPCASEFLAG 65511

// fopen or optional _wfopen to fix long pathname problem of WIN32
LIBHUNSPELL_DLL_EXPORTED FILE* myfopen(const char* path, const char* mode);

// convert UTF-16 characters to UTF-8
LIBHUNSPELL_DLL_EXPORTED std::string& u16_u8(std::string& dest,
                                             const std::vector<w_char>& src);

// convert UTF-8 characters to UTF-16
LIBHUNSPELL_DLL_EXPORTED int u8_u16(std::vector<w_char>& dest,
                                    const std::string& src);

// remove end of line char(s)
LIBHUNSPELL_DLL_EXPORTED void mychomp(char* s);

// duplicate string
LIBHUNSPELL_DLL_EXPORTED char* mystrdup(const char* s);

// strcat for limited length destination string
LIBHUNSPELL_DLL_EXPORTED char* mystrcat(char* dest, const char* st, int max);

// duplicate reverse of string
LIBHUNSPELL_DLL_EXPORTED char* myrevstrdup(const char* s);

// parse into tokens with char delimiter
LIBHUNSPELL_DLL_EXPORTED char* mystrsep(char** sptr, const char delim);
// parse into tokens with char delimiter
LIBHUNSPELL_DLL_EXPORTED char* mystrsep2(char** sptr, const char delim);

// replace pat by rep in word and return word
LIBHUNSPELL_DLL_EXPORTED char* mystrrep(char* word,
                                        const char* pat,
                                        const char* rep);
LIBHUNSPELL_DLL_EXPORTED std::string& mystrrep(std::string& str,
                                               const std::string& search,
                                               const std::string& replace);

// append s to ends of every lines in text
LIBHUNSPELL_DLL_EXPORTED void strlinecat(char* lines, const char* s);

// append s to ends of every lines in text
LIBHUNSPELL_DLL_EXPORTED std::string& strlinecat(std::string& str,
                                                 const std::string& apd);

// tokenize into lines with new line
LIBHUNSPELL_DLL_EXPORTED int line_tok(const char* text,
                                      char*** lines,
                                      char breakchar);

// tokenize into lines with new line and uniq in place
LIBHUNSPELL_DLL_EXPORTED char* line_uniq(char* text, char breakchar);
LIBHUNSPELL_DLL_EXPORTED char* line_uniq_app(char** text, char breakchar);

// change oldchar to newchar in place
LIBHUNSPELL_DLL_EXPORTED char* tr(char* text, char oldc, char newc);

// reverse word
LIBHUNSPELL_DLL_EXPORTED size_t reverseword(std::string& word);

// reverse word
LIBHUNSPELL_DLL_EXPORTED size_t reverseword_utf(std::string&);

// remove duplicates
LIBHUNSPELL_DLL_EXPORTED int uniqlist(char** list, int n);

// free character array list
LIBHUNSPELL_DLL_EXPORTED void freelist(char*** list, int n);

// character encoding information
struct cs_info {
  unsigned char ccase;
  unsigned char clower;
  unsigned char cupper;
};

LIBHUNSPELL_DLL_EXPORTED int initialize_utf_tbl();
LIBHUNSPELL_DLL_EXPORTED void free_utf_tbl();
LIBHUNSPELL_DLL_EXPORTED unsigned short unicodetoupper(unsigned short c,
                                                       int langnum);
LIBHUNSPELL_DLL_EXPORTED w_char upper_utf(w_char u, int langnum);
LIBHUNSPELL_DLL_EXPORTED w_char lower_utf(w_char u, int langnum);
LIBHUNSPELL_DLL_EXPORTED unsigned short unicodetolower(unsigned short c,
                                                       int langnum);
LIBHUNSPELL_DLL_EXPORTED int unicodeisalpha(unsigned short c);

LIBHUNSPELL_DLL_EXPORTED struct cs_info* get_current_cs(const char* es);

// get language identifiers of language codes
LIBHUNSPELL_DLL_EXPORTED int get_lang_num(const char* lang);

// get characters of the given 8bit encoding with lower- and uppercase forms
LIBHUNSPELL_DLL_EXPORTED char* get_casechars(const char* enc);

// convert null terminated string to all caps using encoding
LIBHUNSPELL_DLL_EXPORTED void enmkallcap(char* d,
                                         const char* p,
                                         const char* encoding);

// convert null terminated string to all little using encoding
LIBHUNSPELL_DLL_EXPORTED void enmkallsmall(char* d,
                                           const char* p,
                                           const char* encoding);

// convert std::string to all caps
LIBHUNSPELL_DLL_EXPORTED std::string& mkallcap(std::string& s,
                                               const struct cs_info* csconv);

// convert null terminated string to all little
LIBHUNSPELL_DLL_EXPORTED void mkallsmall(char* p, const struct cs_info* csconv);
// convert null terminated string to all little
LIBHUNSPELL_DLL_EXPORTED std::string& mkallsmall(std::string& s,
                                                 const struct cs_info* csconv);

// convert first letter of string to little
LIBHUNSPELL_DLL_EXPORTED std::string& mkinitsmall(std::string& s,
                                                 const struct cs_info* csconv);

// convert null terminated string to have initial capital
LIBHUNSPELL_DLL_EXPORTED void mkinitcap(char* p, const struct cs_info* csconv);
// convert first letter of string to capital
LIBHUNSPELL_DLL_EXPORTED std::string& mkinitcap(std::string& s,
                                                const struct cs_info* csconv);

// convert first letter of UTF-8 string to capital
LIBHUNSPELL_DLL_EXPORTED std::vector<w_char>&
mkinitcap_utf(std::vector<w_char>& u, int langnum);

// convert UTF-8 string to little
LIBHUNSPELL_DLL_EXPORTED std::vector<w_char>&
mkallsmall_utf(std::vector<w_char>& u, int langnum);

// convert first letter of UTF-8 string to little
LIBHUNSPELL_DLL_EXPORTED std::vector<w_char>&
mkinitsmall_utf(std::vector<w_char>& u, int langnum);

// convert UTF-8 string to capital
LIBHUNSPELL_DLL_EXPORTED std::vector<w_char>&
mkallcap_utf(std::vector<w_char>& u, int langnum);

// get type of capitalization
LIBHUNSPELL_DLL_EXPORTED int get_captype(const std::string& q, cs_info*);

// get type of capitalization (UTF-8)
LIBHUNSPELL_DLL_EXPORTED int get_captype_utf8(const std::vector<w_char>& q, int langnum);

// strip all ignored characters in the string
LIBHUNSPELL_DLL_EXPORTED size_t remove_ignored_chars_utf(
    std::string& word,
    const std::vector<w_char>& ignored_chars);

// strip all ignored characters in the string
LIBHUNSPELL_DLL_EXPORTED size_t remove_ignored_chars(
    std::string& word,
    const std::string& ignored_chars);

LIBHUNSPELL_DLL_EXPORTED int parse_string(char* line, char** out, int ln);

LIBHUNSPELL_DLL_EXPORTED bool parse_array(char* line,
                                          char** out,
                                          std::vector<w_char>& out_utf16,
                                          int utf8,
                                          int ln);

LIBHUNSPELL_DLL_EXPORTED int fieldlen(const char* r);

LIBHUNSPELL_DLL_EXPORTED char* copy_field(char* dest,
                                          const char* morph,
                                          const char* var);
LIBHUNSPELL_DLL_EXPORTED bool copy_field(std::string& dest,
                                         const std::string& morph,
                                         const std::string& var);

LIBHUNSPELL_DLL_EXPORTED int morphcmp(const char* s, const char* t);

LIBHUNSPELL_DLL_EXPORTED int get_sfxcount(const char* morph);

// conversion function for protected memory
LIBHUNSPELL_DLL_EXPORTED void store_pointer(char* dest, char* source);

// conversion function for protected memory
LIBHUNSPELL_DLL_EXPORTED char* get_stored_pointer(const char* s);

// hash entry macros
LIBHUNSPELL_DLL_EXPORTED inline char* HENTRY_DATA(struct hentry* h) {
  char* ret;
  if (!h->var)
    ret = NULL;
  else if (h->var & H_OPT_ALIASM)
    ret = get_stored_pointer(HENTRY_WORD(h) + h->blen + 1);
  else
    ret = HENTRY_WORD(h) + h->blen + 1;
  return ret;
}

LIBHUNSPELL_DLL_EXPORTED inline const char* HENTRY_DATA(
    const struct hentry* h) {
  const char* ret;
  if (!h->var)
    ret = NULL;
  else if (h->var & H_OPT_ALIASM)
    ret = get_stored_pointer(HENTRY_WORD(h) + h->blen + 1);
  else
    ret = HENTRY_WORD(h) + h->blen + 1;
  return ret;
}

// NULL-free version for warning-free OOo build
LIBHUNSPELL_DLL_EXPORTED inline const char* HENTRY_DATA2(
    const struct hentry* h) {
  const char* ret;
  if (!h->var)
    ret = "";
  else if (h->var & H_OPT_ALIASM)
    ret = get_stored_pointer(HENTRY_WORD(h) + h->blen + 1);
  else
    ret = HENTRY_WORD(h) + h->blen + 1;
  return ret;
}

LIBHUNSPELL_DLL_EXPORTED inline char* HENTRY_FIND(struct hentry* h,
                                                  const char* p) {
  return (HENTRY_DATA(h) ? strstr(HENTRY_DATA(h), p) : NULL);
}

#endif
