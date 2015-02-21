require 'json'
require 'open3'

JSON_FILE = "./result.json"
CONFIG = JSON.load( File.read("config.json") )

PURPLE_BACKGROUND = "\033[1;37;45m"
YELLOW = "\033[1;33m"
RED = "\033[0;31m"
LIGHT_BLUE = "\033[1;34m"
RESET = "\033[0m"

@err = nil

def shell(cmd)
  out, err, s = Open3.capture3(cmd)
  @err = err
  return out
end

def printPhase(msg, color)
  puts "#{color}#{msg}#{RESET}"
end

def printLog(msg, color)
  puts "#{color}>>#{RESET} #{msg}"
end

def writeData(lang, value)
  data = JSON.load( File.read(JSON_FILE) )

  data[lang] = {}
  data[lang] = value

  s = JSON.pretty_generate(data)
  File.write(JSON_FILE, s)
end

def bench(lang, phase)
  puts ""
  printPhase " #{lang} language ", PURPLE_BACKGROUND

  conf = CONFIG[lang]
  dir = conf['dir'] || lang
  build = conf['build'] == "yes"
  pattern = conf['pattern']

  commands = JSON.load( File.read("#{dir}/build.json") )

  puts ""

  if phase.include? "version"
    system("#{conf['version']}")
  end

  if phase.include? "build"
    if build == true
      printPhase "=== BUILD ===", YELLOW

      pattern.keys.each do |key|
        build_list = commands["build_" + pattern[key]]
        build_list.keys.each do |key|
          printLog ("cd #{dir}; " + build_list[key]), YELLOW
          `cd #{dir}; #{build_list[key]}`
        end
      end

      puts ""
    end
  end

  if phase.include? "run"
    printPhase "=== RUN ===", RED

    result = {}

    pattern.keys.each do |compiler|
      result[compiler] = {}

      run_list = commands[pattern[compiler]]
      run_list.keys.each do |task|
        printLog ("cd #{dir}; time " + run_list[task]), RED

        out = shell("cd #{dir}; time #{run_list[task]}")
        time = @err.split("\n")[1..-1].join(", ").gsub("\t"," ")
        result[compiler][task] = time

        printLog "[#{task}]: #{result[compiler][task]} ms (result: #{out})", RED
      end
    end

    writeData(lang, result)

    puts ""
  end

  if phase.include? "clean"
    if build == true
      printPhase "=== CLEAN ===", LIGHT_BLUE
      printLog ("cd #{dir}; " + commands['clean']), LIGHT_BLUE
      `cd #{dir}; #{commands['clean']}`
    end
  end

  puts ""
end

def process(phase)
  lang = ARGV[1].split("=")[1] if ARGV[1] != nil
  
  if lang == nil or lang == "all"
    CONFIG.keys.each do |l|
      bench(l,phase)
    end
  elsif CONFIG[lang] != nil
    bench(lang,phase)
  else
    puts "[ERROR] Please select 'lang' from:\n\n  all, #{CONFIG.keys.join(', ')}\n\n"
  end
end

task :all do
  process("build,run,clean")
end

task :version do
  process("version")
end

task :build do
  process("build")
end

task :run do
  process("run")
end

task :clean do
  process("clean")
end