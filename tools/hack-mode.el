;;; References:
;;; - https://ergoemacs.org/emacs/elisp_syntax_coloring.html

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
      ("nop\\|push\\|drop\\|dup\\|plusi\\|minusi\\|multi\\|divi\\|modi\\|plusf\\|minusf\\|multf\\|divf\\|jmp_if\\|jmp\\|eq\\|halt\\|swap\\|not\\|gef\\|gei\\|ret\\|call\\|native\\|andb\\|orb\\|xor\\|shr\\|shl\\|notb\\|read8\\|read16\\|read32\\|read64\\|write8\\|write16\\|write32\\|write64" . font-lock-keyword-face)))

;;;###autoload
(define-derived-mode hack-mode fundamental-mode "hack"
    "Major mode for editing Hack Assembly code."
    (setq font-lock-defaults '(hack-highlights))
    (set-syntax-table hack-mode-syntax-table))

;;;###autoload
(add-to-list 'auto-mode-alist '("\\.hack\\'" . hack-mode))
