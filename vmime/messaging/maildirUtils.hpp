//
// VMime library (http://www.vmime.org)
// Copyright (C) 2002-2005 Vincent Richard <vincent@vincent-richard.net>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef VMIME_MESSAGING_MAILDIRUTILS_HPP_INCLUDED
#define VMIME_MESSAGING_MAILDIRUTILS_HPP_INCLUDED


#include "vmime/utility/file.hpp"
#include "vmime/utility/path.hpp"


namespace vmime {
namespace messaging {


class maildirStore;


/** Miscellaneous helpers functions for maildir messaging system.
  */

class maildirUtils
{
public:

	/** Comparator for message filenames, based only on the
	  * unique identifier part of the filename.
	  */
	class messageIdComparator
	{
	public:

		messageIdComparator(const utility::file::path::component& comp);

		const bool operator()(const utility::file::path::component& other) const;

	private:

		const utility::file::path::component m_comp;
	};

	/** Mode for return value of getFolderFSPath(). */
	enum FolderFSPathMode
	{
		FOLDER_PATH_ROOT,       /**< Root folder. Eg: ~/Mail/MyFolder */
		FOLDER_PATH_NEW,        /**< Folder containing unread messages. Eg: ~/Mail/MyFolder/new */
		FOLDER_PATH_CUR,        /**< Folder containing messages that have been seen. Eg: ~/Mail/MyFolder/cur */
		FOLDER_PATH_TMP,        /**< Temporary folder used for reliable delivery. Eg: ~/Mail/MyFolder/tmp */
		FOLDER_PATH_CONTAINER   /**< Container for sub-folders. Eg: ~/Mail/.MyFolder.directory */
	};

	/** Return the path on the filesystem for the folder in specified store.
	  *
	  * @param store parent store
	  * @param folderPath path of the folder
	  * @param mode type of path to return (see FolderFSPathMode)
	  * @return filesystem path for the specified folder
	  */
	static const utility::file::path getFolderFSPath(maildirStore* store, const utility::path& folderPath, const FolderFSPathMode mode);

	/** Test whether the specified file-system directory corresponds to
	  * a maildir sub-folder. The name of the directory should not start
	  * with '.' to be listed as a sub-folder.
	  *
	  * @param file reference to a file-system directory
	  * @return true if the specified directory is a maildir sub-folder,
	  * false otherwise
	  */
	static const bool isSubfolderDirectory(const utility::file& file);

	/** Extract the unique identifier part of the message filename.
	  * Eg: for the filename "1071577232.28549.m03s:2,RS", it will
	  * return "1071577232.28549.m03s".
	  *
	  * @param filename filename part
	  * @return part of the filename that corresponds to the unique
	  * identifier of the message
	  */
	static const utility::file::path::component extractId(const utility::file::path::component& filename);

	/** Extract message flags from the specified message filename.
	  * Eg: for the filename "1071577232.28549.m03s:2,RS", it will
	  * return (message::FLAG_SEEN | message::FLAG_REPLIED).
	  *
	  * @param comp filename part
	  * @return message flags extracted from the specified filename
	  */
	static const int extractFlags(const utility::file::path::component& comp);

	/** Return a string representing the specified message flags.
	  * Eg: for (message::FLAG_SEEN | message::FLAG_REPLIED), it will
	  * return "RS".
	  *
	  * @param flags set of flags
	  * @return message flags in a string representation
	  */
	static const utility::file::path::component buildFlags(const int flags);

	/** Build a filename with the specified id and flags.
	  *
	  * @param id id part of the filename
	  * @param flags flags part of the filename
	  * @return message filename
	  */
	static const utility::file::path::component buildFilename(const utility::file::path::component& id, const utility::file::path::component& flags);

	/** Build a filename with the specified id and flags.
	  *
	  * @param id id part of the filename
	  * @param flags set of flags
	  * @return message filename
	  */
	static const utility::file::path::component buildFilename(const utility::file::path::component& id, const int flags);

	/** Generate a new unique message identifier.
	  *
	  * @return unique message id
	  */
	static const utility::file::path::component generateId();

private:

	static const vmime::word TMP_DIR;
	static const vmime::word CUR_DIR;
	static const vmime::word NEW_DIR;
};


} // messaging
} // vmime


#endif // VMIME_MESSAGING_MAILDIRUTILS_HPP_INCLUDED