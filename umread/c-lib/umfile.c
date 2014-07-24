#include <stdio.h>
#include <unistd.h>

#include "umfileint.h"

int get_type_and_length(int word_size,
			const void *int_hdr,
			Data_type *type_rtn,
			size_t *num_words_rtn)
{
  errorhandle_init();
  switch (word_size)
    {
    case 4:
      return get_type_and_length_core_sgl(int_hdr, type_rtn, num_words_rtn);
    case 8:
      return get_type_and_length_core_dbl(int_hdr, type_rtn, num_words_rtn);
    default:
      return -1;
    }
}

int detect_file_type(int fd, File_type *file_type)
{
  errorhandle_init();
  return detect_file_type_(fd, file_type);
}


int read_header(int fd,
		size_t header_offset,
		Byte_ordering byte_ordering, 
		int word_size, 
		void *int_hdr_rtn,
		void *real_hdr_rtn)
{
  errorhandle_init();
  switch (word_size)
    {
    case 4:
      return read_hdr_at_offset_sgl(fd, header_offset, byte_ordering, 
				    int_hdr_rtn, real_hdr_rtn);
    case 8:
      return read_hdr_at_offset_dbl(fd, header_offset, byte_ordering, 
				    int_hdr_rtn, real_hdr_rtn);
    default:
      return -1;
    }
}


File *file_parse(int fd,
		 File_type file_type)
{
  File *file;

  errorhandle_init();

  switch (file_type.word_size)
    {
    case 4:
      CKP(  file = file_parse_core_sgl(fd, file_type)  );
      break;
    case 8:
      CKP(  file = file_parse_core_dbl(fd, file_type)  );
      break;
    default:
      ERR;
    }
  return file;
  ERRBLKP;
}


void file_free(File *file)
{
  errorhandle_init();

  CKI(   free_file(file)   );
  return;

 err:
  GRIPE;
}