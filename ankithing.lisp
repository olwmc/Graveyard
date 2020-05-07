(defparameter lis ())
(defparameter temp ())

(defun parse-text (inp &optional (in nil))
  (when inp
    (let ((item (car inp))
	  (rest (cdr inp)))

      (cond ((equal item "") 
	     (parse-text rest in))

	    ((equal item "[")
	     (parse-text rest t))

	    ((equal item "]")
	     (progn
	       (push (reverse temp) lis)
	       (setf temp ())
	       (parse-text rest nil)))
	    
	    (in
	      (progn
	        (push item temp)
		(parse-text rest t)))))))

(defun read-file (filename)
  (with-open-file (stream filename)
    (loop for line = (read-line stream nil)
	  while line
	  collect line)))

(defun write-file (inp)
  (with-open-file (out "foo" 
		       :direction :output
		       :if-exists :supersede)
   (dolist (i inp)
    (princ (format nil "~a,~{ ~a~};~%" (car i) (cdr i)) out))))

(defun parse-file (name)
  (parse-text (read-file name))
  (write-file lis))

(parse-file "sm.txt")
(quit)
