from subprocess import Popen, PIPE

bin_path = '/home/lezh1k/SRC/work/MDPet/sourcemappings/bin/sourcmappings_finder'
src_file_path = '/home/lezh1k/SRC/test_data/sourcemapping'


process = Popen([bin_path, "-sm_file_path", src_file_path, "-sm_node_index", "3"], stdout=PIPE)
(output, err) = process.communicate()
exit_code = process.wait()
print(output)