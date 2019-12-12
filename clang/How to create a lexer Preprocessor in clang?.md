# How to create a lexer Preprocessor in clang?

​	Generally, There are the steps below to create a lexer a Preprocessor:

 1. Specific the input-data and get a `std::unique_ptr` pointing at `llvm::MemoryBuffer` by invoking `llvm::MemoryBuffer::getMemBuffer`,

    e.g.:

    ```c++
    std::unique_ptr<llvm::MemoryBuffer> Buf = llvm::MemoryBuffer::getMemBuffer(/*type->StringRef*/InputData);
    ```

 2. Invoking `SourceManager::setMainFileID()` function, Let SourceManager's object handle the MemoryBuffer objects. At the moment, SourceManager will assigns unique FileID for each unique #include clain.

    The SourceManager can be queried for information about SourceLocation objects, turning them into either spelling or expansion locations. Spelling locations represent where the bytes corresponding to a token came from and expansion locations represent where the location is in the user's view. In the case of a macro expansion, for example, the spelling location indicates where the expanded token came from and the expansion location specifies where it was expaned.

    e.g.:

    ```c++
    SourceMgr.setMainFileID(SourceMgr.createFileID(std::move(Buf)));
    ```

    The `SourceMgr.createFileID()` Function creates a new FileID that represents the specified memory buffer. This does not caching of the buffer , instead takes ownership of the MemoryBuffer, so only pass a MemoryBuffer to this once.

 3. Create a HeaderSearch instance

    ```c++
    HeaderSearch HeaderInfo(std::make_shared<HearderSearchOptions>(),
                           /*type->SourceManager*/SourceMgr,
                           /*type->DiagnosticsEngine*/Diags,
                           /*type->LangOptions*/LangOpts,
                           /*type->TargetInfo pointer*/TargInfoPtr);
    ```

    `HeaderSearch` encapsulates the information needed to find the file referenced by a #include or #include_next etc.

    DiagnosticsEngine` is Concrete class, and it used by the frontend to report problems and issues. This massages the diagnostics (e.g. handling things like "report warnings as errors") and passes them off to the DiagnosticConsumer for reporting to the user. DiagnosticsEngine is tied to one translation unit and one SourceManager.

    `LangOptions` keeps track of the various options that can be enabled, which controls the dialect of C or C++ that is accepted.

    `TargetInfo` exposes information about the current target.

    `IntrusiveRefCntPtr`,a smart pointer to a reference-counted object that inherits from `RefCountedBase` or `ThreadSafeRefCountedBase`. This class increments its pointee's reference count when it is created, and decrements its refcount when it's destroyed ( or is changed to point to a different object).

 4. Create Preprocessor

    ```c++
    std::unique_ptr<Preprocessor> PP = llvm::make_unique<Preprocessor>(
    std::make_shared<PreprocessOptions>(),
        /*type->DiagnosticsEngine*/Diags,
        /*type->LangOptions*/LangOpts,
        /*type->SourceManager*/SourceMgr,
        /*type->HeaderSearch*/HeaderInfo,
        /*type->TrivialModuleLoader*/ModLoader,
        /*IILookup = */ nullptr,
        /*OwnsHeaderSearch = */false);
    ```

    `TrivialModuleLoader` is a module loader that does not know to load moudles.

 5. Initialize the preprocessor using information about the target.

    ```c++
    PP->Initialize(/*type-> TargetInfo*/TargInfo);
    ```

    The param of `Targinfo` is owned by the caller and must remain valid for the lifetime of the preprocessor.

 6. EnterMainSourceFile to Enter the specified FileID as the main source file, which implicitly adds the builtin defines etc.

    ```c++
    PP->EnterMainSourceFile();
    ```

    