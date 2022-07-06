;;; hack-mode.el --- Major mode for editing Hack Assembly code -*- lexical-binding: t -*-

;; Copyright (c) 2022 Frexs

;; Author: Frexs <frexs.dev@gmail.com>
;; URL: https://github.com/frexsdev/hvm

;; Permission is hereby granted, free of charge, to any person obtaining a copy
;; of this software and associated documentation files (the Software), to deal
;; in the Software without restriction, including without limitation the rights
;; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
;; copies of the Software, and to permit persons to whom the Software is
;; furnished to do so, subject to the following conditions:

;; The above copyright notice and this permission notice shall be included in all
;; copies or substantial portions of the Software.

;; THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
;; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
;; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
;; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
;; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
;; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
;; SOFTWARE.

;;; Commentary:
;;
;; Major mode for editing Hack Assembly code. The language for simple Virtual Machine.

(defvar hack-mode-syntax-table nil "Syntax table for `hack-mode`.")

(setq hack-mode-syntax-table
    (let ((syn-table (make-syntax-table)))
        ;; assembly style comment: "; ..."
        (modify-syntax-entry ?\; "<" syn-table)
        (modify-syntax-entry ?\n ">" syn-table)
        syn-table))

(setq hack-highlights
    '(("%[[:word:]_]+" . font-lock-preprocessor-face)
      ("[[:word:]_]+\\:" . font-lock-constant-face)
      ("nop\\|push\\|drop\\|dup\\|plusi\\|minusi\\|multi\\|divi\\|modi\\|plusf\\|minusf\\|multf\\|divf\\|jmp_if\\|jmp\\|eqi\\|eqf\\|halt\\|swap\\|not\\|gef\\|gei\\|ret\\|call\\|native\\|andb\\|orb\\|xor\\|shr\\|shl\\|notb\\|read8\\|read16\\|read32\\|read64\\|write8\\|write16\\|write32\\|write64" . font-lock-keyword-face)))

;;;###autoload
(define-derived-mode hack-mode fundamental-mode "hack"
    "Major mode for editing Hack Assembly code."
    (setq font-lock-defaults '(hack-highlights))
    (set-syntax-table hack-mode-syntax-table))

;;;###autoload
(add-to-list 'auto-mode-alist '("\\.hack\\'" . hack-mode))

(provide 'hack-mode)

;;; hack-mode.el ends here
