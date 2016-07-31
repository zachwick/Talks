;; sent-mode.el --- Major mode for making presentations with sent -*- lexical-binding: t; -*-

;; Copyright (C) 2016 zach wick <zach@zachwick.com>

;; Author: zach wick <zach@zachwick.com>
;; Maintainer: zach wick <zach@zachwick.com>
;; Created: July 16, 2016
;; Version: 1.0.0
;; Package-Requires: ((emacs "24"))
;; Keywords: sent, takahashi, presentation
;; URL: https://github.com/zachwick/sent-mode

;; This file is not part of GNU Emacs.

;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.

;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to the Free Software
;; Foundation, Inc., 51 Franklin Street, Fifth Floor,
;; Boston, MA 02110-1301, USA.

(require 'generic-x) ;; we need this

(define-generic-mode
    'sent-mode                         ;; name of the mode to create
  '("#")                               ;; comments start with '!!'
  '("@")                               ;; some keywords
  nil
  '("\\.sent$")                        ;; files for which to activate this mode
  nil                                  ;; other functions to call
  "A mode for sent presentation files" ;; doc string for this mode
  )

(provide 'sent-mode)
