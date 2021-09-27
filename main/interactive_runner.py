from __future__ import print_function
import sys, subprocess, threading

class SubprocessThread(threading.Thread):
  def __init__(self,
               args,
               stdin_pipe=subprocess.PIPE,
               stdout_pipe=subprocess.PIPE,
               stderr_pipe=subprocess.PIPE):
    threading.Thread.__init__(self)
    self.p = subprocess.Popen(
        args,
        stdin=stdin_pipe,
        stdout=stdout_pipe,
        stderr=stderr_pipe)

  def run(self):
    try:
      self.return_code = self.p.wait()
      self.stdout = "" if self.p.stdout is None else self.p.stdout.read()
      self.stderr = "" if self.p.stderr is None else self.p.stderr.read()
    except (SystemError, OSError):
      self.return_code = -1
      self.stdout = ""
      self.stderr = "The process crashed or produced too much output."

assert sys.argv.count("--") == 1, (
    "There should be exactly one instance of '--' in the command line.")
sep_index = sys.argv.index("--")
judge_args = sys.argv[1:sep_index]
sol_args = sys.argv[sep_index + 1:]

t_sol = SubprocessThread(sol_args)
t_judge = SubprocessThread(judge_args, stdin_pipe=t_sol.p.stdout,
                           stdout_pipe=t_sol.p.stdin)
t_sol.start()
t_judge.start()
t_sol.join()
t_judge.join()
print("Judge return code:", t_judge.return_code)
print("Judge standard error:", t_judge.stderr.decode())
print("Solution return code:", t_sol.return_code)
print("Solution standard error:", t_sol.stderr.decode())
