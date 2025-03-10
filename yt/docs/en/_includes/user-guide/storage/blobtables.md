# Binary data in tables

This section contains information about how to use tables to store binary data.

## General information { #common }

You sometimes need to save binary data from jobs.
The obvious solution is to write a file from each job to Cypress.
But this method has its drawbacks:

- It creates a high load on the proxy.
- A large number of objects appears in Cypress which makes working with them less efficient.

Therefore, it is preferable to write the binary data in a single table:

1. The data is divided into parts and saved in separate table rows. This table must have a set of key columns that uniquely identify the file: name and path. Besides that, there must be a column responsible for the [BLOB](https://en.wikipedia.org/wiki/BLOB) number with the data and a column responsible for the data itself. The table must be sorted by a set of key columns and by a column with the BLOB number so that point reads by the key that specifies the file name are possible.
2. For the file, all BLOBs, except for the last one, must have the same size, for example, 4 MB. The columns with data and the BLOB number must be named `data` and `part_index`, respectively.

Tables that meet the described conditions are BLOB tables.

BLOB tables are used within {{product-name}} to store stderr and core files generated by operation jobs.
For example, the table with stderr operations has 3 columns: `job_id`, `part_index`, and `data`, the table is sorted by `job_id` and `part_index`.

## The read_blob_table command { #read_blob_table }

The special `read_blob_table` command is implemented for convenient data reading from BLOB tables.

The command takes the path to the table as input and outputs a binary data stream.
The command also checks that the indexes of read BLOBs start from zero and go without gaps.

The command has the `part_index_column_name` and `data_column_name` parameters that enable you to set the names of columns with the BLOB number and data, respectively. By default, these names are `part_index` and `data`.

Starting the operation and reading job stderr from the table with BLOB:

{% list tabs %}

- Python

   ```bash
   yt.run_map("....; echo 'something' >&2;", "//tmp/input", "//tmp/output", stderr_table="//tmp/stderr_table")
   ```

- CLI

   ```
   yt read-blob-table '//tmp/stderr_table["cc26aa85-a694bf6b-3fe0384-963"]'
   ```

{% endlist %}

