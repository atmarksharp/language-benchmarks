require 'json'

JSON_FILE = "./result.json"
CONFIG = JSON.load( File.read("config.json") )

PURPLE_BACKGROUND = "\033[1;37;45m"
YELLOW = "\033[1;33m"
RED = "\033[0;31m"
LIGHT_BLUE = "\033[1;34m"
RESET = "\033[0m"

def printPhase(msg, color)
  puts "#{color}#{msg}#{RESET}"
end

def printLog(msg, color)
  puts "#{color}>>#{RESET} #{msg}"
end

def writeData(lang, key, value)
  data = JSON.load( File.read(JSON_FILE) )

  data[lang] = {}
  data[lang][key] = value

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

    pattern.keys.each do |key|
      result = {}

      run_list = commands[pattern[key]]
      run_list.keys.each do |key|
        printLog ("cd #{dir}; " + run_list[key]), RED

        arr = (1..5).map do
          s = `cd #{dir}; #{run_list[key]}`.gsub(/[\n\r\t ]/,'')
          Float(s)
        end

        n = (arr.inject(:+)/arr.length)
        result[key] = "%0.7f"%n

        printLog "[#{key}]: #{result[key]}", RED
      end

      writeData(lang, key, result)
    end

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

task :build do
  process("build")
end

task :run do
  process("run")
end

task :clean do
  process("clean")
end