;;; References:
;;; - https://ergoemacs.org/emacs/elisp_syntax_coloring.html

(setq hack-highlights
    '(("nop\\|push\\|drop\\|dup\\|plusi\\|minusi\\|multi\\|divi\\|modi\\|plusf\\|minusf\\|multf\\|divf\\|jmp_if\\|jmp\\|eq\\|halt\\|swap\\|not\\|gef\\|gei\\|ret\\|call\\|native\\|andb\\|orb\\|xor\\|shr\\|shl\\|notb\\|read8\\|read16\\|read32\\|read64\\|write8\\|write16\\|write32\\|write64" . font-lock-keyword-face)))

(define-derived-mode hack-mode fundamental-mode "hack"
    "Major mode for editing Hack Assembly code."
    (setq font-lock-defaults '(hack-highlights)))
